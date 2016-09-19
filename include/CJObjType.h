#ifndef CJObjType_H
#define CJObjType_H

#include <CJNameSpace.h>
#include <CJToken.h>

class CJObjType : public CJNameSpace, public std::enable_shared_from_this<CJObjType> {
 public:
  typedef std::set<std::string>                 Functions;
  typedef std::vector<CJValueP>                 Values;
  typedef std::map<std::string,CJFunctionBaseP> NameFunctions;

 public:
  CJObjType(CJavaScript *js, const CJToken::Type type, const std::string &name);

  const CJToken::Type &type() const { return type_; }

  const std::string &name() const { return name_; }

  virtual CJObjTypeP parentType() const { return CJObjTypeP(); }

  CJObjTypeFunctionP typeFunction() const { return typeFn_; }
  void setTypeFunction(CJObjTypeFunctionP typeFn) { typeFn_ = typeFn; }

  const NameFunctions &typeFunctions() const { return typeFunctions_; }

  const NameFunctions &objFunctions() const { return objFunctions_; }

  void addTypeFunction(CJavaScript *js, const std::string &name);
  void addObjectFunction(CJavaScript *js, const std::string &name);

  virtual CJValueP construct(CJavaScript *, const Values &) { return CJValueP(); }

  CJValueP getProperty(CJavaScript *js, const std::string &key) const override;

  KeyNames getTypePropertyNames() const;

  bool isInstanceOf(CJObjTypeP type) const;

  // exec function for type
  virtual CJValueP execType(CJavaScript *, const std::string &, const Values &) {
    return CJValueP();
  }

  // exec function for object of type
  virtual CJValueP exec(CJavaScript *, const std::string &, const Values &) {
    return CJValueP();
  }

  virtual void print(std::ostream &os) const {
    os << name_;
  }

  friend std::ostream &operator<<(std::ostream &os, const CJObjType &rhs) {
    rhs.print(os);

    return os;
  }

 protected:
  CJavaScript*       js_ { 0 };
  CJToken::Type      type_;
  std::string        name_;
  CJObjTypeFunctionP typeFn_;
  NameFunctions      typeFunctions_;
  NameFunctions      objFunctions_;
};

#endif
