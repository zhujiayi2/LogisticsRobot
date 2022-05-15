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

#endif  // LANG_FEATURES_H_
