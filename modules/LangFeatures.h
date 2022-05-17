#ifndef LANG_FEATURES_H_
#define LANG_FEATURES_H_

namespace disable_constructors {
    class Singleton {
    public:
        Singleton(const Singleton &) = delete;

        Singleton &operator=(const Singleton &) = delete;

        Singleton(Singleton &&) = delete;

        Singleton &operator=(Singleton &&) = delete;

    protected:
        Singleton() = default;

        ~Singleton() = default;
    };

    class Module : public Singleton {
    public:
        Module() = delete;

        ~Module() = default;
    };
}

#define SINGLETON public disable_constructors::Singleton

#define MODULE public disable_constructors::Module

#endif  // LANG_FEATURES_H_
