#include "pa.string_tilde.h"
#include "StringModel.h"

#define _USE_MATH_DEFINES
#include <math.h>

static t_int *pa_string_tilde_perform(t_int *w) {
  t_pa_string_tilde *x = (t_pa_string_tilde *) (w[1]);
  t_sample *in1 = (t_sample *) (w[2]);
  t_sample *in2 = (t_sample *) (w[3]);
  t_sample *out1 = (t_sample *) (w[4]);
  int n = (int) (w[5]);

  const float sr = x->m_sr;
  float freq = 0.f;
  float phase_inc = 0.f;
  float phase = x->m_phase;

  while (n--) {
    freq = eigenFrequency(*in1++, 12); //*in1++;

    *out1++ = cosf((float) (phase * 2.f * M_PI));

    phase_inc = (freq / sr);

    if (phase >= 1.f) phase -= 1.f;
    if (phase < 0.f) phase += 1.f;

    phase += phase_inc;
  }

  x->m_phase = phase;

  return (w + 6);
}

static void pa_string_tilde_dsp(t_pa_string_tilde *x, t_signal **sp) {

  // Store samplerate
  x->m_sr = sys_getsr();

  dsp_add(pa_string_tilde_perform, 5,
          x,
          sp[0]->s_vec, // Inlet 0
          sp[1]->s_vec, // Inlet 1
          sp[2]->s_vec, // Outlet 0
          sp[0]->s_n); // Vectorsize
}

static void *pa_string_tilde_new(t_symbol *s, int argc, t_atom *argv) {
  t_pa_string_tilde *x = (t_pa_string_tilde *) pd_new(pa_string_tilde_class);
  if (x) {
    x->m_phase = 0.f;

    signalinlet_new((t_object *) x, 0);
    x->m_out = outlet_new((t_object *)x, &s_signal);
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
  }

  pa_string_tilde_class = c;
}
