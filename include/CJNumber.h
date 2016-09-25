#ifndef CJNumber_H
#define CJNumber_H

#include <CJObj.h>
#include <CJUtil.h>
#include <limits>
#include <sstream>

// Number Type
class CJNumberType : public CJObjType {
 public:
  static CJObjTypeP instance(CJavaScript *js);

  CJNumberType(CJavaScript *js);

  CJValueP getProperty(CJavaScript *js, const std::string &key) const override;

  CJValueP execType(CJavaScript *js, const std::string &name, const Values &values) override;

  CJValueP exec(CJavaScript *js, const std::string &name, const Values &values) override;

 private:
  static CJObjTypeP type_;
};

//------

// Number Value
class CJNumber : public CJObj {
 public:
  enum class RealType {
    NaN,
    PosInf,
    NegInf
  };

 public:
  CJNumber(CJavaScript *js, double real=0.0);

  CJNumber *dup(CJavaScript *js) const override { return new CJNumber(js, real_); }

  bool isPrimitive() const override { return primitive_; }
  void setIsPrimitive(bool b) { primitive_ = b; }

  bool isNumber() const override { return true; }

  std::string toString() const override;

  double real() const { return real_; }
  void setReal(double r) { real_ = r; }

  bool isInteger() const { return CJUtil::isInteger(real_); }

  double toReal() const override { return real_; }

  bool toBoolean() const override { return (real_ != 0.0); }

  bool hasProperty() const override { return ! isPrimitive(); }

  std::string realString() const;

  int cmp(const CJValue *v) const override {
    double r1 =    toReal();
    double r2 = v->toReal();

    if (r1 < r2) return -1;
    if (r1 > r2) return  1;

    return 0;
  }

 private:
  double real_ { 0.0 };
  bool   primitive_ { true };
};

#endif
