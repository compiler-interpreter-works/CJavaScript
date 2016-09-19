#ifndef CJObjectFunction_H
#define CJObjectFunction_H

#include <CJObjTypeFunction.h>

// Object constructor function
class CJObjectFunction : public CJObjTypeFunction {
 public:
  CJObjectFunction(CJavaScript *js);

  CJValue *dup(CJavaScript *js) const override { return new CJObjectFunction(js); }

  CJValueP exec(CJavaScript *js, const Values &values) override;

  void print(std::ostream &os) const override {
    os << "[Function: Object]";
  }
};

typedef std::shared_ptr<CJObjectFunction> CJObjectFunctionP;

#endif
