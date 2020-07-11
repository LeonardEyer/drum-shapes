/*
 // Copyright (c) 2016 Eliott Paris, paccpp, Université Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

// A string object that select outlet based on input atoms.

#include <m_pd.h> // puredata header

static t_class *pa_string_class;

typedef struct t_pa_string {
  t_object m_obj;          // pd object - always placed in first in the object's struct

  t_outlet *eigenFrequencies[10];

} t_pa_string;

static void pa_string_float(t_pa_string *x, float stringLength) {
  post("float method called");
  for (int i = 0; i < 10; ++i) {
    // TODO: Add multiple float inputs (Tension / Density)
    // TODO: Compute eigen frequencies using tension/density
    // TODO: What does stringLength mean in cm?
    // TODO: Find out about weights
    float freq = stringLength * ((i+1) / 2);
    outlet_float(x->eigenFrequencies[i], freq);
  }
}

static void *pa_string_new(t_symbol *name, int argc, t_atom *argv) {
  t_pa_string *x = (t_pa_string *) pd_new(pa_string_class);

  if (x) {
    post("string : number of args = %i", argc);

    int i = 0;
    for (; i < argc; ++i) {
      if (argv[i].a_type == A_FLOAT) {
        float flottant = argv[i].a_w.w_float;
        post("arg %i (float) = %f", i, flottant);
      } else if (argv[i].a_type == A_SYMBOL) {
        t_symbol *s = argv[i].a_w.w_symbol;
        post("arg %i (symbol) = %s", i, s->s_name);
      }
    }

    inlet_new((t_object *) x, &x->m_obj.ob_pd, 0, 0); // declare a new general inlet

    // Generate one outlet for every eigen frequency
    for (int j = 0; j < 10; ++j) {
      x->eigenFrequencies[j] = outlet_new((t_object *) x, gensym("float"));
    }
  }

  return (x);
}

static void pa_string_free(t_pa_string *x) {
  ; // nothing to be done here.
}

extern void setup_pa0x2estring(void) {
  t_class *c = class_new(gensym("pa.string"),
                         (t_newmethod) pa_string_new, (t_method) pa_string_free,
                         sizeof(t_pa_string), CLASS_DEFAULT, A_GIMME, 0);
  if (c) {
    class_addmethod(c, (t_method) pa_string_float, gensym("float"), A_FLOAT, 0);
  }

  pa_string_class = c;
}
