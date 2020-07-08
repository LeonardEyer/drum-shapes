/*
// Copyright (c) 2016 Eliott Paris.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// A string for Pd signal objects

#include <m_pd.h>

static t_class *pa_string_tilde_class;

typedef struct pa_string_tilde {
  t_object m_obj; // pd object - always placed in first in the object's struct
  t_float m_f;
} t_pa_string_tilde;

static t_int *pa_string_tilde_perform(t_int *w);

static void pa_string_tilde_dsp(t_pa_string_tilde *x, t_signal **sp);

static void *pa_string_tilde_new(t_symbol *s, int argc, t_atom *argv);

static void pa_string_tilde_free(t_pa_string_tilde *x);

extern void setup_pa0x2estring_tilde(void);
