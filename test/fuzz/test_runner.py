#!/usr/bin/env python3
# Copyright (c) 2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Run fuzz test targets.
"""

import argparse
import configparser
import os
import sys
import subprocess
import logging

# Fuzzers known to lack a seed corpus in https://github.com/bitcoin-core/qa-assets/tree/master/fuzz_seed_corpus
FUZZERS_MISSING_CORPORA = [
]


def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument(
        "-l",
        "--loglevel",
        dest="loglevel",
        default="INFO",
        help="log events at this level and higher to the console. Can be set to DEBUG, INFO, WARNING, ERROR or CRITICAL. Passing --loglevel DEBUG will output all logs to console.",
    )
    parser.add_argument(
        '--export_coverage',
        action='store_true',
        help='If true, export coverage information to files in the seed corpus',
    )
    parser.add_argument(
        '--valgrind',
        action='store_true',
        help='If true, run fuzzing binaries under the valgrind memory error detector',
    )
    parser.add_argument(
        '-x',
        '--exclude',
        help="A comma-separated list of targets to exclude",
    )
    parser.add_argument(
        'seed_dir',
        help='The seed corpus to run on (must contain subfolders for each fuzz target).',
    )
    parser.add_argument(
        'target',
        nargs='*',
        help='The target(s) to run. Default is to run all targets.',
    )

    args = parser.parse_args()

    # Set up logging
    logging.basicConfig(
        format='%(message)s',
        level=int(args.loglevel) if args.loglevel.isdigit() else args.loglevel.upper(),
    )

    # Read config generated by configure.
    config = configparser.ConfigParser()
    configfile = os.path.abspath(os.path.dirname(__file__)) + "/../config.ini"
    config.read_file(open(configfile, encoding="utf8"))

    if not config["components"].getboolean("ENABLE_FUZZ"):
        logging.error("Must have fuzz targets built")
        sys.exit(1)

    # Build list of tests
    test_list_all = parse_test_list(makefile=os.path.join(config["environment"]["SRCDIR"], 'src', 'Makefile.test.include'))

    if not test_list_all:
        logging.error("No fuzz targets found")
        sys.exit(1)

    logging.debug("{} fuzz target(s) found: {}".format(len(test_list_all), " ".join(sorted(test_list_all))))

    args.target = args.target or test_list_all  # By default run all
    test_list_error = list(set(args.target).difference(set(test_list_all)))
    if test_list_error:
        logging.error("Unknown fuzz targets selected: {}".format(test_list_error))
    test_list_selection = list(set(test_list_all).intersection(set(args.target)))
    if not test_list_selection:
        logging.error("No fuzz targets selected")
    if args.exclude:
        for excluded_target in args.exclude.split(","):
            if excluded_target not in test_list_selection:
                logging.error("Target \"{}\" not found in current target list.".format(excluded_target))
                continue
            test_list_selection.remove(excluded_target)
    test_list_selection.sort()

    logging.info("{} of {} detected fuzz target(s) selected: {}".format(len(test_list_selection), len(test_list_all), " ".join(test_list_selection)))

    try:
        help_output = subprocess.run(
            args=[
                os.path.join(config["environment"]["BUILDDIR"], 'src', 'test', 'fuzz', test_list_selection[0]),
                '-help=1',
            ],
            timeout=20,
            check=True,
            stderr=subprocess.PIPE,
            universal_newlines=True,
        ).stderr
        if "libFuzzer" not in help_output:
            logging.error("Must be built with libFuzzer")
            sys.exit(1)
    except subprocess.TimeoutExpired:
        logging.error("subprocess timed out: Currently only libFuzzer is supported")
        sys.exit(1)

    run_once(
        corpus=args.seed_dir,
        test_list=test_list_selection,
        build_dir=config["environment"]["BUILDDIR"],
        export_coverage=args.export_coverage,
        use_valgrind=args.valgrind,
    )


def run_once(*, corpus, test_list, build_dir, export_coverage, use_valgrind):
    for t in test_list:
        corpus_path = os.path.join(corpus, t)
        if t in FUZZERS_MISSING_CORPORA:
            os.makedirs(corpus_path, exist_ok=True)
        args = [
            os.path.join(build_dir, 'src', 'test', 'fuzz', t),
            '-runs=1',
            corpus_path,
        ]
        if use_valgrind:
            args = ['valgrind', '--quiet', '--error-exitcode=1'] + args
        logging.debug('Run {} with args {}'.format(t, args))
        result = subprocess.run(args, stderr=subprocess.PIPE, universal_newlines=True)
        output = result.stderr
        logging.debug('Output: {}'.format(output))
        try:
            result.check_returncode()
        except subprocess.CalledProcessError as e:
            if e.stdout:
                logging.info(e.stdout)
            if e.stderr:
                logging.info(e.stderr)
            logging.info("Target \"{}\" failed with exit code {}: {}".format(t, e.returncode, " ".join(args)))
            sys.exit(1)
        if not export_coverage:
            continue
        for l in output.splitlines():
            if 'INITED' in l:
                with open(os.path.join(corpus, t + '_coverage'), 'w', encoding='utf-8') as cov_file:
                    cov_file.write(l)
                    break


def parse_test_list(makefile):
    with open(makefile, encoding='utf-8') as makefile_test:
        test_list_all = []
        read_targets = False
        for line in makefile_test.readlines():
            line = line.strip().replace('test/fuzz/', '').replace(' \\', '')
            if read_targets:
                if not line:
                    break
                test_list_all.append(line)
                continue

            if line == 'FUZZ_TARGETS =':
                read_targets = True
    return test_list_all


if __name__ == '__main__':
    main()
