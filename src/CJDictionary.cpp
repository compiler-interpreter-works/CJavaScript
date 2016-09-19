#include <CJDictionary.h>
#include <CJGetterSetter.h>
#include <CJavaScript.h>

CJObjTypeP CJDictionaryType::type_;

CJObjTypeP
CJDictionaryType::
instance(CJavaScript *js)
{
  if (! type_) {
    type_ = CJObjTypeP(new CJDictionaryType(js));

    js->addObjectType("dictionary", type_);
  }

  return type_;
}

CJDictionaryType::
CJDictionaryType(CJavaScript *js) :
 CJObjType(js, CJToken::Type::Dictionary, "dictionary")
{
}

CJValueP
CJDictionaryType::
exec(CJavaScript *, const std::string &, const Values &)
{
  return CJValueP();
}

//------

CJDictionary::
CJDictionary(CJavaScript *js, CJObjTypeP type) :
 CJValue(type), CJNameSpace(), js_(js)
{
}

CJDictionary::
CJDictionary(CJavaScript *js, const std::string &name, const KeyValues &keyValues) :
 CJValue(CJDictionaryType::instance(js)), CJNameSpace(keyValues), js_(js), name_(name)
{
}

std::string
CJDictionary::
toString() const
{
  CJValueP prop = getProperty(js_, "toString");

  if (prop) {
    CJFunctionBaseP fn = js_->valueToFunction(prop);

    if (fn) {
      CJFunctionBase::Values values;

      CJValueP value = fn->exec(js_, values);

      if (value)
        return value->toString();
    }

    return "";
  }
  else {
    std::ostringstream ss; ss << *this;

    return ss.str();
  }
}

CJValueP
CJDictionary::
getProperty(CJavaScript *js, const std::string &key) const
{
  CJValueP propVal = CJNameSpace::getProperty(js, key);

  if (propVal && propVal->type() == CJToken::Type::GetterSetter) {
    CJGetterSetterP gs = std::static_pointer_cast<CJGetterSetter>(propVal);

    CJDictionary *th = const_cast<CJDictionary *>(this);

    CJDictionaryP dict = std::static_pointer_cast<CJDictionary>(th->shared_from_this());

    js->pushThis(dict);

    propVal = gs->getValue();

    js->popThis();
  }

  return propVal;
}

void
CJDictionary::
setProperty(CJavaScript *js, const std::string &key, CJValueP value)
{
  CJValueP propVal = getProperty(js, key);

  if (propVal && propVal->type() == CJToken::Type::GetterSetter) {
    CJGetterSetterP gs = std::static_pointer_cast<CJGetterSetter>(propVal);

    CJDictionaryP dict = std::static_pointer_cast<CJDictionary>(shared_from_this());

    js->pushThis(dict);

    gs->setValue(value);

    js->popThis();

    return;
  }

  CJNameSpace::setProperty(js, key, value);
}

bool
CJDictionary::
hasPropertyValue(const std::string &key) const
{
  return CJNameSpace::hasProperty(js_, key);
}

CJValueP
CJDictionary::
propertyValue(const std::string &key) const
{
  return CJNameSpace::getProperty(js_, key);
}

void
CJDictionary::
setPropertyValue(const std::string &key, CJValueP value)
{
  CJNameSpace::setProperty(js_, key, value);
}

void
CJDictionary::
deletePropertyValue(const std::string &key)
{
  CJNameSpace::deleteProperty(key);
}

bool
CJDictionary::
isReadOnlyProperty(const std::string &ind) const
{
  auto p = readOnly_.find(ind);

  return (p != readOnly_.end());
}

void
CJDictionary::
setReadOnlyProperty(const std::string &ind, bool b)
{
  if (b)
    readOnly_.erase(ind);
  else
    readOnly_.insert(ind);
}

std::vector<std::string>
CJDictionary::
getFunctionNames() const
{
  std::vector<std::string> names;

  for (const auto &f : keyValues_) {
    if (f.second->isFunction())
      names.push_back(f.first);
  }

  return names;
}

std::vector<std::string>
CJDictionary::
getVariableNames() const
{
  std::vector<std::string> names;

  for (const auto &v : keyValues_) {
    if (v.second->type() == CJToken::Type::Var)
      names.push_back(v.first);
  }

  return names;
}

CJValue::KeyNames
CJDictionary::
propertyNames() const
{
  CJValue::KeyNames names;

  for (auto &kv : keyValues())
    names.push_back(kv.first);

  return names;
}

void
CJDictionary::
print(std::ostream &os) const
{
  int i = 0;

  if (name_ != "")
    os << name_ << " ";

  os << "{";

  for (auto &kv : keyValues()) {
    if (i > 0)
      os << ",";

    os << " " << kv.first << ": ";

    if (kv.second)
      os << *kv.second;
    else
      os << "<null>";

    ++i;
  }

  if (i > 0)
    os << " ";

  os << "}";
}
