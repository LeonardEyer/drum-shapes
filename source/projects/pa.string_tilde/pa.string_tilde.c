/*
 // Copyright (c) 2016 Eliott Paris.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

//! @brief A simple sinusoidal oscillator.

#include <m_pd.h>

#define _USE_MATH_DEFINES
#include <math.h> // cos...
#include <stdlib.h>
#include "StringVibration.h"

static t_class *pa_string_tilde_class;

typedef struct _pa_string_tilde {
  t_object m_obj;

  float m_sr;
  float m_phase;

  t_outlet *m_out;

  t_float m_f;

} t_pa_string_tilde;

static void pa_string_tilde_bang(t_pa_string_tilde *x) {
  x->m_phase = 0;
}

static t_int *pa_string_tilde_perform(t_int *w) {
  t_pa_string_tilde *x = (t_pa_string_tilde *) (w[1]);
  t_sample *in = (t_sample *) (w[2]);
  t_sample *out = (t_sample *) (w[3]);
  int n = (int) (w[4]);

  const float sr = x->m_sr;
  float freq = 0.f;
  float L = 0.f;
  float phase_inc = 0.f;
  float phase = x->m_phase;

  string s;
  s.density = 7.726f;
  s.tension = 13.1f;
  s.diameter = 0.00899f;

  while (n--) {
    L = fabsf(*in++);
    s.length = L;

    *out++ = u(s, 0.25f * L, phase);

    freq = base_freq(s);

    phase_inc = (freq / sr);

    phase += phase_inc;
    // Clip at 16
    phase = phase > 16 ? 16 : phase;
  }

  x->m_phase = phase;

  return (w + 5);
}

static void pa_string_tilde_dsp(t_pa_string_tilde *x, t_signal **sp) {
  x->m_sr = sys_getsr();

  dsp_add(pa_string_tilde_perform, 4,
          x,
          sp[0]->s_vec,   // inlet 0
          sp[1]->s_vec,   // outlet 0
          sp[0]->s_n);    // vectorsize
}

static void *pa_string_tilde_new(t_symbol *s, int argc, t_atom *argv) {
  t_pa_string_tilde *x = (t_pa_string_tilde *) pd_new(pa_string_tilde_class);
  if (x) {
    x->m_phase = 0.f;
    x->m_out = outlet_new((t_object *) x, &s_signal);
  }

  return (x);
}

static void pa_string_tilde_free(t_pa_string_tilde *x) {
  outlet_free(x->m_out);
}

extern void setup_pa0x2estring_tilde(void) {
  t_class *c = class_new(gensym("pa.string~"),
                         (t_newmethod) pa_string_tilde_new, (t_method) pa_string_tilde_free,
                         sizeof(t_pa_string_tilde), CLASS_DEFAULT, A_GIMME, 0);
  if (c) {
    CLASS_MAINSIGNALIN(c, t_pa_string_tilde, m_f);
    class_addmethod(c, (t_method) pa_string_tilde_dsp, gensym("dsp"), A_CANT);
    class_addbang(c, (t_method) pa_string_tilde_bang);
  }

  pa_string_tilde_class = c;
}
