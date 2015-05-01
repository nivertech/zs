/*  =========================================================================
    zs_core_fsm - No title state machine engine

    ** WARNING *************************************************************
    THIS SOURCE FILE IS 100% GENERATED. If you edit this file, you will lose
    your changes at the next build cycle. This is great for temporary printf
    statements. DO NOT MAKE ANY CHANGES YOU WISH TO KEEP. The correct places
    for commits are:

     * The XML model used for this code generation: zs_core.xml, or
     * The code generation script that built this file: fsm_c
    ************************************************************************
    =========================================================================
*/


//  ---------------------------------------------------------------------------
//  State machine constants

typedef enum {
    running_state = 1,
    expecting_open_state = 2,
    composing_state = 3,
    defaults_state = 4
} state_t;

typedef enum {
    NULL_event = 0,
    number_event = 1,
    string_event = 2,
    function_event = 3,
    compose_event = 4,
    eol_event = 5,
    open_event = 6,
    close_event = 7,
    invalid_event = 8
} event_t;

//  Names for state machine logging and error reporting
static char *
s_state_name [] = {
    "(NONE)",
    "running",
    "expecting_open",
    "composing",
    "defaults"
};

static char *
s_event_name [] = {
    "(NONE)",
    "number",
    "string",
    "function",
    "compose",
    "eol",
    "open",
    "close",
    "invalid"
};

//  Action prototypes
static void push_number_to_output (zs_core_t *self);
static void get_next_token (zs_core_t *self);
static void push_string_to_output (zs_core_t *self);
static void execute_function (zs_core_t *self);
static void name_must_be_unknown (zs_core_t *self);
static void open_composition (zs_core_t *self);
static void show_pipe_contents (zs_core_t *self);
static void signal_success (zs_core_t *self);
static void compose_number_value (zs_core_t *self);
static void compose_string_value (zs_core_t *self);
static void compose_function (zs_core_t *self);
static void close_composition (zs_core_t *self);
static void signal_syntax_error (zs_core_t *self);

//  This is the context block for a FSM thread; use the setter
//  methods to set the FSM properties.

typedef struct {
    zs_core_t *parent;          //  Parent class
    bool animate;               //  Animate state machine
    state_t state;              //  Current state
    event_t event;              //  Current event
    event_t next_event;         //  The next event
    event_t exception;          //  Exception event, if any
    uint64_t cycles;            //  Track the work done
} fsm_t;

static fsm_t *
fsm_new (zs_core_t *parent)
{
    fsm_t *self = (fsm_t *) zmalloc (sizeof (fsm_t));
    if (self) {
        self->state = running_state;
        self->event = NULL_event;
        self->parent = parent;
    }
    return self;
}

static void
fsm_destroy (fsm_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        fsm_t *self = *self_p;
        free (self);
        *self_p = NULL;
    }
}

static void
fsm_set_next_event (fsm_t *self, event_t next_event)
{
    self->next_event = next_event;
}

static void
fsm_set_exception (fsm_t *self, event_t exception)
{
    self->exception = exception;
}

static void
fsm_set_animate (fsm_t *self, bool animate)
{
    self->animate = animate;
}

static uint64_t
fsm_cycles (fsm_t *self)
{
    return self->cycles;
}


//  Execute state machine until it has no next event. Before calling this
//  you must have set the next event using fsm_set_next_event(). Ends when
//  there is no next event set.

static void
fsm_execute (fsm_t *self)
{
    while (self->next_event != NULL_event) {
        self->cycles++;
        self->event = self->next_event;
        self->next_event = NULL_event;
        self->exception = NULL_event;
        if (self->animate) {
            zsys_debug ("zs_core: %s:", s_state_name [self->state]);
            zsys_debug ("zs_core:           %s", s_event_name [self->event]);
        }
        if (self->state == running_state) {
            if (self->event == number_event) {
                if (!self->exception) {
                    //  push_number_to_output
                    if (self->animate)
                        zsys_debug ("zs_core:               $ push_number_to_output");
                    push_number_to_output (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
            }
            else
            if (self->event == string_event) {
                if (!self->exception) {
                    //  push_string_to_output
                    if (self->animate)
                        zsys_debug ("zs_core:               $ push_string_to_output");
                    push_string_to_output (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
            }
            else
            if (self->event == function_event) {
                if (!self->exception) {
                    //  execute_function
                    if (self->animate)
                        zsys_debug ("zs_core:               $ execute_function");
                    execute_function (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
            }
            else
            if (self->event == compose_event) {
                if (!self->exception) {
                    //  name_must_be_unknown
                    if (self->animate)
                        zsys_debug ("zs_core:               $ name_must_be_unknown");
                    name_must_be_unknown (self->parent);
                }
                if (!self->exception) {
                    //  open_composition
                    if (self->animate)
                        zsys_debug ("zs_core:               $ open_composition");
                    open_composition (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
                if (!self->exception)
                    self->state = expecting_open_state;
            }
            else
            if (self->event == eol_event) {
                if (!self->exception) {
                    //  show_pipe_contents
                    if (self->animate)
                        zsys_debug ("zs_core:               $ show_pipe_contents");
                    show_pipe_contents (self->parent);
                }
                if (!self->exception) {
                    //  signal_success
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_success");
                    signal_success (self->parent);
                }
            }
            else
            if (self->event == open_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == close_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == invalid_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else {
                //  Handle unexpected internal events
                zsys_warning ("zs_core: unhandled event %s in %s",
                    s_event_name [self->event], s_state_name [self->state]);
                assert (false);
            }
        }
        else
        if (self->state == expecting_open_state) {
            if (self->event == open_event) {
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
                if (!self->exception)
                    self->state = composing_state;
            }
            else
            if (self->event == number_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == string_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == function_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == compose_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == close_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == invalid_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == eol_event) {
                if (!self->exception) {
                    //  signal_success
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_success");
                    signal_success (self->parent);
                }
            }
            else {
                //  Handle unexpected internal events
                zsys_warning ("zs_core: unhandled event %s in %s",
                    s_event_name [self->event], s_state_name [self->state]);
                assert (false);
            }
        }
        else
        if (self->state == composing_state) {
            if (self->event == number_event) {
                if (!self->exception) {
                    //  compose_number_value
                    if (self->animate)
                        zsys_debug ("zs_core:               $ compose_number_value");
                    compose_number_value (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
            }
            else
            if (self->event == string_event) {
                if (!self->exception) {
                    //  compose_string_value
                    if (self->animate)
                        zsys_debug ("zs_core:               $ compose_string_value");
                    compose_string_value (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
            }
            else
            if (self->event == function_event) {
                if (!self->exception) {
                    //  compose_function
                    if (self->animate)
                        zsys_debug ("zs_core:               $ compose_function");
                    compose_function (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
            }
            else
            if (self->event == close_event) {
                if (!self->exception) {
                    //  close_composition
                    if (self->animate)
                        zsys_debug ("zs_core:               $ close_composition");
                    close_composition (self->parent);
                }
                if (!self->exception) {
                    //  get_next_token
                    if (self->animate)
                        zsys_debug ("zs_core:               $ get_next_token");
                    get_next_token (self->parent);
                }
                if (!self->exception)
                    self->state = running_state;
            }
            else
            if (self->event == compose_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == open_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == invalid_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == eol_event) {
                if (!self->exception) {
                    //  signal_success
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_success");
                    signal_success (self->parent);
                }
            }
            else {
                //  Handle unexpected internal events
                zsys_warning ("zs_core: unhandled event %s in %s",
                    s_event_name [self->event], s_state_name [self->state]);
                assert (false);
            }
        }
        else
        if (self->state == defaults_state) {
            if (self->event == number_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == string_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == function_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == compose_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == open_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == close_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == invalid_event) {
                if (!self->exception) {
                    //  signal_syntax_error
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_syntax_error");
                    signal_syntax_error (self->parent);
                }
            }
            else
            if (self->event == eol_event) {
                if (!self->exception) {
                    //  signal_success
                    if (self->animate)
                        zsys_debug ("zs_core:               $ signal_success");
                    signal_success (self->parent);
                }
            }
            else {
                //  Handle unexpected internal events
                zsys_warning ("zs_core: unhandled event %s in %s",
                    s_event_name [self->event], s_state_name [self->state]);
                assert (false);
            }
        }
        //  If we had an exception event, interrupt normal programming
        if (self->exception) {
            if (self->animate)
                zsys_debug ("zs_core:               ! %s", s_event_name [self->exception]);
            self->next_event = self->exception;
        }
        else
        if (self->animate)
            zsys_debug ("zs_core:               > %s", s_state_name [self->state]);
    }
}