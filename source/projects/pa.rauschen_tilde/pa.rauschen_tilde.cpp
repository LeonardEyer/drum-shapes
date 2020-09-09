/*
// Copyright (c) 2016 Eliott Paris.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

// A starter for Pd signal objects

#include <m_pd.h>
#include "Filter.hpp"

static t_class *pa_rauschen_tilde_class;

typedef struct pa_rauschen_tilde {
  t_object m_obj; // pd object - always placed in first in the object's struct
  t_float m_f;

  Filter *f;         // Adaptive Filter
  t_clock *m_clock;  // Clock

  t_outlet *list_out; // List outlet
  t_atom list[10]; // The list

} t_pa_rauschen_tilde;

static t_int *pa_rauschen_tilde_perform(t_int *w) {
  auto *x = (t_pa_rauschen_tilde *) (w[1]);
  auto *in1 = (t_sample *) (w[2]);
  auto *in2 = (t_sample *) (w[3]);
  auto *out1 = (t_sample *) (w[4]);
  int n = (int) (w[5]);

  int i;
  for (i = 0; i < n; ++i) {
    double y = x->f->process(*in1++);
    double err = *in2++ - y;
    x->f->update_weights(err);
    *out1++ = y;
  }

  // Copy all the coefficient values to the atom list
  for (int j = 0; j < 10; ++j) {
    SETFLOAT(x->list + j, *(x->f->get_coeffs() + j));
  }

  clock_set(x->m_clock, 0.f);

  return (w + 6);
}

void pa_rauschen_tilde_tick(pa_rauschen_tilde *x) {
  outlet_list(x->list_out, &s_list, 10, x->list);
}

static void pa_rauschen_tilde_dsp(t_pa_rauschen_tilde *x, t_signal **sp) {
  dsp_add(pa_rauschen_tilde_perform, 5,
          x,
          sp[0]->s_vec, sp[1]->s_vec,
          sp[2]->s_vec,
          sp[0]->s_n);
}

static void *pa_rauschen_tilde_new(t_symbol *s, int argc, t_atom *argv) {
  auto *x = (t_pa_rauschen_tilde *) pd_new(pa_rauschen_tilde_class);
  if (x) {
    signalinlet_new((t_object *) x, 0);
    outlet_new((t_object *) x, &s_signal);

    x->list_out = outlet_new(&x->m_obj, &s_list);
    x->m_clock = clock_new(x, (t_method) pa_rauschen_tilde_tick);

    x->f = new Filter(10, 0.01);
  }

  return (x);
}

static void pa_rauschen_tilde_free(t_pa_rauschen_tilde *x) {
  ;
}

// Note in c++ you need to wrap the setup method in an extern "C" statement.
extern "C" {
extern void setup_pa0x2erauschen_tilde(void) {
  t_class *c = class_new(gensym("pa.rauschen~"),
                         (t_newmethod) pa_rauschen_tilde_new, (t_method) pa_rauschen_tilde_free,
                         sizeof(t_pa_rauschen_tilde), CLASS_DEFAULT, A_GIMME, 0);
  if (c) {
    CLASS_MAINSIGNALIN(c, t_pa_rauschen_tilde, m_f);
    class_addmethod(c, (t_method) pa_rauschen_tilde_dsp, gensym("dsp"), A_CANT);
  }

  pa_rauschen_tilde_class = c;
}
}
