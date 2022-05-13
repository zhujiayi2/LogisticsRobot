#ifndef LANG_FEATURES_H_
#define LANG_FEATURES_H_

namespace disable_constructors {
    class DisableMoveConstructor {
    public:
        DisableMoveConstructor() = default;

        ~DisableMoveConstructor() = default;

        DisableMoveConstructor(DisableMoveConstructor &&) = delete;

        DisableMoveConstructor &operator=(DisableMoveConstructor &&) = delete;

        DisableMoveConstructor(const DisableMoveConstructor &) = default;

        DisableMoveConstructor &operator=(const DisableMoveConstructor &) = default;
    };

    class DisableCopyConstructor {
    public:
        DisableCopyConstructor() = default;

        ~DisableCopyConstructor() = default;

        DisableCopyConstructor(const DisableCopyConstructor &) = delete;

        DisableCopyConstructor &operator=(const DisableCopyConstructor &) = delete;

        DisableCopyConstructor(DisableCopyConstructor &&) = default;

        DisableCopyConstructor &operator=(DisableCopyConstructor &&) = default;
    };
}

#define NO_COPY public disable_constructors::DisableCopyConstructor

#define NO_MOVE public disable_constructors::DisableMoveConstructor

#define SELF (*this)

#define ATTR_READER(_var, _func)  \
    inline auto _func() const { return _var; }
#define ATTR_READER_REF(_var, _func)  \
    inline auto &_func() const { return _var; }

#define VIRTUAL_ATTR_READER(_type, _var, _func)  \
    virtual _type _func() const { return _var; }

#define OVERRIDE_ATTR_READER(_type, _var, _func)  \
    inline _type _func() const override { return _var; }

#endif  // LANG_FEATURES_H_
