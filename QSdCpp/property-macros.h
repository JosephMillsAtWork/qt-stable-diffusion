#ifndef PROPERTY_MACROS_H
#define PROPERTY_MACROS_H
#include <QObject>

#define QP_RW(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name WRITE set_##name NOTIFY name##Changed RESET reset_##name) \
    private: \
    type m_##name = default_##name (); \
    static const type & default_##name (void) { \
        static const type value = defaultValue; \
        return value; \
    } \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    public Q_SLOTS: \
    void set_##name (const type & name) { \
        if (m_##name != name) { \
            m_##name = name; \
            Q_EMIT name##Changed (m_##name); \
        } \
    } \
    void reset_##name (void) { \
        set_##name ( default_##name ( ) ) ; \
    } \
    Q_SIGNALS: \
    void name##Changed (const type & name); \
    private:

#define QP_RO(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name NOTIFY name##Changed RESET reset_##name STORED true) \
    private: \
    type m_##name = default_##name ( ); \
    static const type & default_##name ( ) { \
        static const type value = defaultValue; \
        return value; \
    } \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    void set_##name (const type & name) { \
        if (m_##name != name) { \
            m_##name = name; \
            Q_EMIT name##Changed (m_##name); \
        } \
    } \
    void reset_##name (void) { \
        set_##name ( default_##name ( ) ) ; \
    }\
    Q_SIGNALS: \
    void name##Changed (const type & name); \
    private:

#define QP_CONST(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name CONSTANT STORED true) \
    private: \
    type m_##name = defaultValue; \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    private:

#define QP_MEMBER(type, name, defaultValue) \
    protected: \
    Q_PROPERTY(type name MEMBER m_##name) \
    private: \
    type m_##name = defaultValue;


//////////////////
/// REQUIRED TYPES
///////////////////


#define QP_RW_REQ(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name WRITE set_##name NOTIFY name##Changed RESET reset_##name REQUIRED) \
    private: \
    type m_##name = default_##name ( ); \
    static const type & default_##name ( void ) { \
        static const type value = defaultValue ; \
        return value ; \
    } \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    public Q_SLOTS: \
    void set_##name (const type & name) { \
        if (m_##name != name) { \
            m_##name = name; \
            Q_EMIT name##Changed (m_##name); \
        } \
    } \
    void reset_##name (void) { \
        set_##name ( default_##name ( ) ) ; \
    } \
    Q_SIGNALS: \
    void name##Changed (const type & name); \
    private:

#define QP_RO_REQ(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name NOTIFY name##Changed RESET reset_##name STORED true REQUIRED) \
    private: \
    type m_##name = default_##name ( ); \
    static const type & default_##name ( ) { \
        static const type value = defaultValue; \
        return value; \
    } \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    void set_##name (const type & name) { \
        if (m_##name != name) { \
            m_##name = name; \
            Q_EMIT name##Changed (m_##name); \
        } \
    } \
    void reset_##name (void) { \
        set_##name ( default_##name ( ) ) ; \
    }\
    Q_SIGNALS: \
    void name##Changed (const type & name); \
    private:

#define QP_CONST_REQ(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name CONSTANT STORED true REQUIRED) \
    private: \
    type m_##name = defaultValue; \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    private:

#define QP_MEMBER_REQ(type, name, defaultValue) \
protected: \
    Q_PROPERTY(type name MEMBER m_##name REQUIRED) \
    private: \
    type m_##name = defaultValue;



#define QP_RW_SAVE(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name WRITE set_##name NOTIFY name##Changed RESET reset_##name) \
    private: \
    type m_##name = default_##name (); \
    static const type & default_##name (void) { \
        static const type value = defaultValue; \
        return value; \
    } \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    public Q_SLOTS: \
    void set_##name (const type & name) { \
        if (m_##name != name) { \
            m_##name = name; \
            Q_EMIT save (); \
            Q_EMIT name##Changed (m_##name); \
        } \
    } \
    void reset_##name (void) { \
        set_##name ( default_##name ( ) ) ; \
    } \
    Q_SIGNALS: \
    void name##Changed (const type & name); \
    private:


#define QP_RO_SAVE(type, name, defaultValue) \
    protected: \
    Q_PROPERTY (type name READ get_##name NOTIFY name##Changed RESET reset_##name STORED true) \
    private: \
    type m_##name = default_##name ( ); \
    static const type & default_##name ( ) { \
        static const type value = defaultValue; \
        return value; \
    } \
    public: \
    const type & get_##name (void) const {  return m_##name ;  } \
    void set_##name (const type & name) { \
        if (m_##name != name) { \
            m_##name = name; \
            Q_EMIT save (); \
            Q_EMIT name##Changed (m_##name); \
        } \
    } \
    void reset_##name (void) { \
        set_##name ( default_##name ( ) ) ; \
    }\
    Q_SIGNALS: \
    void name##Changed (const type & name); \
    private:



//////////////////
/// FROM other Sttruct Pointer's
///////////////////

#define QP_STRUCT_SIMPLE_RW(type, name, structName, structMember) \
    protected: \
    Q_PROPERTY(type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
    type m_##name{}; \
    public: \
    type get_##name(void) const { \
        if (structName) \
        return structName->structMember; \
        return m_##name; \
    } \
    public Q_SLOTS: \
    void set_##name(const type &name) { \
        if (m_##name == name) return; \
        m_##name = name; \
        if (structName) \
            structName->structMember = m_##name; \
        Q_EMIT name##Changed(m_##name); \
    } \
    Q_SIGNALS: \
    void name##Changed(const type &name); \
    private:

#define QP_STRUCT_SIMPLE_RO(type, name, structName, structMember) \
    protected: \
    Q_PROPERTY(type name READ get_##name NOTIFY name##Changed) \
    private: \
    type m_##name{}; \
    public: \
    type get_##name(void) const { \
        if (structName) return structName->structMember; \
        return m_##name; \
    } \
    void set_##name(const type &name) { \
        if (m_##name == name) return; \
        m_##name = name; \
        if (structName) \
            structName->structMember = m_##name; \
        Q_EMIT name##Changed(m_##name); \
    } \
    Q_SIGNALS: \
    void name##Changed(const type &name); \
    private:



#define QP_STRUCT_CHAR_RW(name, structName, structMember) \
    protected: \
    Q_PROPERTY(QString name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
    QString    m_##name; \
    QByteArray m_##name##_bytes; \
    public: \
    QString get_##name(void) const { \
        if (!structName) \
            return QString{}; \
        if (!structName->structMember) \
            return QString{}; \
        return QString::fromLatin1(structName->structMember); \
    } \
    public Q_SLOTS: \
    void set_##name(const QString &name) { \
        if (m_##name == name) \
            return; \
        m_##name = name; \
        m_##name##_bytes = m_##name.toLatin1(); \
        if (structName) \
            structName->structMember = m_##name##_bytes.constData(); \
        Q_EMIT name##Changed(m_##name); \
    } \
    Q_SIGNALS: \
    void name##Changed(const QString &name); \
    private:

#define QP_STRUCT_CHAR_RO(name, structName, structMember) \
    protected: \
    Q_PROPERTY(QString name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
    QString    m_##name; \
    QByteArray m_##name##_bytes; \
    public: \
    QString get_##name(void) const { \
        if (!structName) \
            return QString{}; \
        if (!structName->structMember) \
            return QString{}; \
        return QString::fromLatin1(structName->structMember); \
    } \
    public Q_SLOTS: \
    void set_##name(const QString &name) { \
        if (m_##name == name) \
            return; \
        m_##name = name; \
        m_##name##_bytes = m_##name.toLatin1(); \
        if (structName) \
            structName->structMember = m_##name##_bytes.constData(); \
        Q_EMIT name##Changed(m_##name); \
    } \
    Q_SIGNALS: \
    void name##Changed(const QString &name); \
    private:


#define QP_STRUCT_CHAR_CONST_RO(name, structName, structMember) \
    protected: \
    Q_PROPERTY(QString name READ get_##name NOTIFY name##Changed) \
    public: \
    QString get_##name(void) const { \
        if (!structName) return QString{}; \
        if (!structName->structMember) return QString{}; \
        return QString::fromLatin1(structName->structMember); \
    } \
    void set_##name(const QString &name) { \
        Q_UNUSED(name) \
        Q_EMIT name##Changed(get_##name()); \
    } \
    Q_SIGNALS: \
    void name##Changed(const QString &name); \
    private:

#define QP_STRUCT_CHAR_CONST_RW(name, structName, structMember) \
    protected: \
    Q_PROPERTY(QString name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
    QString m_##name; \
    public: \
    QString get_##name(void) const { \
        if (structName && structName->structMember) return QString::fromLatin1(structName->structMember); \
        return m_##name; \
    } \
    public Q_SLOTS: \
    void set_##name(const QString &name) { \
        if (m_##name != name) { \
            m_##name = name; \
            Q_EMIT name##Changed(m_##name); \
        } \
    } \
    Q_SIGNALS: \
    void name##Changed(const QString &name); \
    private:


#endif // PROPERTY-MACROS_H
