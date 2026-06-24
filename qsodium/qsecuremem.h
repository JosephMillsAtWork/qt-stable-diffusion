#pragma once

#include <QByteArray>
#include <QString>

#include <cstddef>
#include <cstring>
#include <sodium/utils.h>

class QSecureMem
{
public:

    explicit QSecureMem(size_t size = 0);
    QSecureMem(const QSecureMem &other);
    QSecureMem &operator=(const QSecureMem &other);
    QSecureMem(QSecureMem &&other) noexcept;
    QSecureMem &operator=(QSecureMem &&other) noexcept;
    ~QSecureMem();


    [[nodiscard]] bool allocate(size_t size);
    void copyFrom(const void *src, size_t len);
    void clear() noexcept;
    void free() noexcept;

    [[nodiscard]] unsigned char *data() noexcept;
    [[nodiscard]] const unsigned char *data() const noexcept;
    [[nodiscard]] qsizetype size() const noexcept;

    [[nodiscard]] QString toString() const;
    [[nodiscard]] QString toBase64(int variant = sodium_base64_VARIANT_ORIGINAL) const;
    bool fromBase64(const QString &encoded, int variant = sodium_base64_VARIANT_ORIGINAL);
    [[nodiscard]] QString fromBase64toString(const QString &encoded,
                                                 int variant = sodium_base64_VARIANT_ORIGINAL) const;

    [[nodiscard]] bool operator==(const QSecureMem &other) const noexcept;
    [[nodiscard]] bool operator!=(const QSecureMem &other) const noexcept;

private:
    unsigned char *m_data{nullptr};
    qsizetype m_size{0};
};


