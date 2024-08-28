#ifndef __FSM_HH__
#define __FSM_HH__

template <class T> class FSM
{
    T m_state;

  public:
    FSM(T);
    ~FSM() = default;

    T state() const { return m_state; }
    void transition(T);
    virtual inline void pre_transition(T new_state) { (void)new_state; }
    virtual inline void post_transition(T old_state) { (void)old_state; }
};

template <class State> FSM<State>::FSM(State initial) : m_state(initial) {}

template <class State> void FSM<State>::transition(State new_state)
{
    pre_transition(new_state);
    m_state = new_state;
    post_transition(m_state);
}

#endif
