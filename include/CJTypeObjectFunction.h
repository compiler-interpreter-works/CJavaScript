#ifndef CJTypeObjectFunction_H
#define CJTypeObjectFunction_H

#include <CJFunction.h>

class CJTypeObjectFunction : public CJFunction {
 public:
  CJTypeObjectFunction(CJavaScript *js, CJObjTypeP obj, const std::string &name);

  CJValue *dup(CJavaScript *js) const override {
    return new CJTypeObjectFunction(js, objType_, name_);
  }

  bool hasObjectValue() const override { return hasObjValue_; }
  void setHasObjectValue(bool b) { hasObjValue_ = b; }

  CJValueP exec(CJavaScript *js, const Values &values);

 private:
  CJObjTypeP  objType_;
  std::string name_;
  bool        hasObjValue_ { true };
};

typedef std::shared_ptr<CJTypeObjectFunction> CJTypeObjectFunctionP;

#endif
