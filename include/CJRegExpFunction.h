#ifndef CJRegExpFunction_H
#define CJRegExpFunction_H

#include <CJObjTypeFunction.h>

// string function
class CJRegExpFunction : public CJObjTypeFunction {
 public:
  CJRegExpFunction(CJavaScript *js);

  CJValue *dup(CJavaScript *js) const override { return new CJRegExpFunction(js); }

  CJValueP exec(CJavaScript *js, const Values &values) override;

  void print(std::ostream &os) const override {
    os << "[Function: RegExp]";
  }
};

#endif
