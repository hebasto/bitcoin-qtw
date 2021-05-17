#!/usr/bin/env python3
# Copyright (c) 2012-2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
'''
Extract _("...") strings for translation and convert to Qt stringdefs so that
they can be picked up by Qt linguist.
'''
from subprocess import Popen, PIPE
import operator
import os
import sys

OUT_CPP="qt/bitcoinstrings.cpp"
EMPTY=['""']

def parse_po(text):
    """
    Parse 'po' format produced by xgettext.
    Return a list of (msgid,msgstr) tuples.
    """
    messages = []
    msgid = []
    msgstr = []
    in_msgid = False
    in_msgstr = False

    for line in text.split('\n'):
        line = line.rstrip('\r')
        if line.startswith('msgid '):
            if in_msgstr:
                messages.append((msgid, msgstr))
                in_msgstr = False
            # message start
            in_msgid = True

            msgid = [line[6:]]
        elif line.startswith('msgstr '):
            in_msgid = False
            in_msgstr = True
            msgstr = [line[7:]]
        elif line.startswith('"'):
            if in_msgid:
                msgid.append(line)
            if in_msgstr:
                msgstr.append(line)

    if in_msgstr:
        messages.append((msgid, msgstr))

    return messages

files = sys.argv[1:]

# xgettext -n --keyword=_ $FILES
XGETTEXT=os.getenv('XGETTEXT', 'xgettext')
if not XGETTEXT:
    print('Cannot extract strings: xgettext utility is not installed or not configured.',file=sys.stderr)
    print('Please install package "gettext" and re-run \'./configure\'.',file=sys.stderr)
    sys.exit(1)
child = Popen([XGETTEXT,'--output=-','--from-code=utf-8','-n','--keyword=_'] + files, stdout=PIPE)
(out, err) = child.communicate()

messages = parse_po(out.decode('utf-8'))

f = open(OUT_CPP, 'w', encoding="utf8")
f.write("""

#include <QtGlobal>

// Automatically generated by extract_strings_qt.py
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
""")
f.write('static const char UNUSED *bitcoin_strings[] = {\n')
f.write('QT_TRANSLATE_NOOP("bitcoin-core", "%s"),\n' % (os.getenv('COPYRIGHT_HOLDERS'),))
messages.sort(key=operator.itemgetter(0))
for (msgid, msgstr) in messages:
    if msgid != EMPTY:
        f.write('QT_TRANSLATE_NOOP("bitcoin-core", %s),\n' % ('\n'.join(msgid)))
f.write('};\n')
f.close()
