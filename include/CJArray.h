#ifndef CJArray_H
#define CJArray_H

#include <CJObj.h>
#include <deque>
#include <vector>

// Array Type
class CJArrayType : public CJObjType {
 public:
  static CJObjTypeP instance(CJavaScript *js);

  CJArrayType(CJavaScript *js);

  CJValueP execType(CJavaScript *js, const std::string &name, const Values &values) override;

  CJValueP exec(CJavaScript *js, const std::string &name, const Values &values) override;

 private:
  static CJObjTypeP type_;
};

//-------

// Array Value
class CJArray : public CJObj {
 public:
  struct PropertyData {
    COptBool canDelete;
    COptBool writable;
    COptBool enumerable;
  };

  typedef std::deque<CJValueP>       Values;
  typedef std::map<int,PropertyData> PropertyMap;

 public:
  CJArray(CJavaScript *js, int n=0);
  CJArray(CJavaScript *js, const Values &values);
  CJArray(CJavaScript *js, const std::vector<CJValueP> &values);

  CJArray *dup(CJavaScript *js) const override { return new CJArray(js, values_); }

  bool isArray() const override { return true; }

  Values values() const { return values_; }
  void setValues(const Values &values) { values_ = values; }

  void setValues(const std::vector<CJValueP> &values);

  std::string toString() const override {
    std::ostringstream ss; ss << *this;

    return ss.str();
  }

  double toReal() const override { return 0; }

  bool toBoolean() const override { return ! values_.empty(); }

  void addValue(CJValueP value);

  CJValueP removeValue();

  void addFrontValue(CJValueP value);

  CJValueP removeFrontValue();

  bool hasIndex() const override { return true; }
  bool hasIndexValue(int ind) const override;
  CJValueP indexValue(int ind) const override;
  void setIndexValue(int ind, CJValueP value) override;
  void deleteIndexValue(int ind) override;

  bool canDeleteIndex(int ind) const;
  void setCanDeleteIndex(int ind, bool b);

  bool isWritableIndex(int ind) const override;
  void setWritableIndex(int ind, bool b) override;

  bool isEnumerableIndex(int ind) const;
  void setEnumerableIndex(int ind, bool b=true);

  bool hasValue(CJValueP value) const;

  long length() const override { return values_.size(); }

  void reverse();

  void sort();

  CJValueP getProperty(CJavaScript *js, const std::string &key) const override;
  void setProperty(CJavaScript *js, const std::string &key, CJValueP value) override;

  void print(std::ostream &os) const override;

 protected:
  Values      values_;
  PropertyMap propertyMap_;
};

#endif
