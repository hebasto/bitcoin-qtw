#ifndef BITCOINUNITS_H
#define BITCOINUNITS_H

#include <QString>
#include <QAbstractListModel>

// Bitcoin unit definitions
class BitcoinUnits: public QAbstractListModel
{
public:
    explicit BitcoinUnits(QObject *parent);

    enum Unit
    {
        // Source: https://en.bitcoin.it/wiki/Units
        // Please add only sensible ones
        BTC,
        mBTC,
        uBTC
    };

    /// Static API
    // Get list of units, for dropdown box
    static QList<Unit> availableUnits();
    // Short name
    static QString name(int unit);
    // Longer description
    static QString description(int unit);
    // Number of satoshis / unit
    static qint64 factor(int unit);
    // Number of amount digits (to represent max number of coins)
    static int amountDigits(int unit);
    // Number of decimals left
    static int decimals(int unit);
    // Format as string
    static QString format(int unit, qint64 amount, bool plussign=false);
    // Format as string (with unit)
    static QString formatWithUnit(int unit, qint64 amount, bool plussign=false);
    // Parse string to coin amount
    static bool parse(int unit, const QString &value, qint64 *val_out);

    /// AbstractListModel implementation
    enum {
        // Unit identifier
        UnitRole = Qt::UserRole
    } RoleIndex;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
private:
    QList<BitcoinUnits::Unit> unitlist;
};
typedef BitcoinUnits::Unit BitcoinUnit;

#endif // BITCOINUNITS_H
