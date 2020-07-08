#include "pa.string_tilde.h"

static t_int *pa_string_tilde_perform(t_int *w) {
  //t_pa_string_tilde   *x   = (t_pa_string_tilde *)(w[1]);
  t_sample *in1 = (t_sample *) (w[2]);
  t_sample *in2 = (t_sample *) (w[3]);
  t_sample *out1 = (t_sample *) (w[4]);
  int n = (int) (w[5]);

  int i;
  for (i = 0; i < n; ++i) {
    *out1++ = *in1++ + *in2++;
  }

  return (w + 6);
}

static void pa_string_tilde_dsp(t_pa_string_tilde *x, t_signal **sp) {
  dsp_add(pa_string_tilde_perform, 5,
          x,
          sp[0]->s_vec, sp[1]->s_vec,
          sp[2]->s_vec,
          sp[0]->s_n);
}

static void *pa_string_tilde_new(t_symbol *s, int argc, t_atom *argv) {
  t_pa_string_tilde *x = (t_pa_string_tilde *) pd_new(pa_string_tilde_class);
  if (x) {
    signalinlet_new((t_object *) x, 0);
    outlet_new((t_object *) x, &s_signal);
  }

  return (x);
}

static void pa_string_tilde_free(t_pa_string_tilde *x) {
  ;
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
