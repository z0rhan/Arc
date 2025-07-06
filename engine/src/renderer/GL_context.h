#ifndef GL_CONTEXT_HH
#define GL_CONTEXT_HH

class Context
{
public:
    virtual ~Context() = default;

    virtual bool init() = 0;
    virtual void swapContext() = 0;
};

#endif // GL_CONTEXT_hh