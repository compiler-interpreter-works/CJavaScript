#include <CJExecIdentifiers.h>
#include <CJavaScript.h>

CJExecIdentifiers::
CJExecIdentifiers() :
 CJToken(CJToken::Type::Identifiers)
{
}

CJValueP
CJExecIdentifiers::
exec(CJavaScript *js)
{
  if (evalue_) {
    if (identifiers_.empty())
      return CJValueP();

    const std::string &name1 = identifiers_[0]->name();

    if (evalue_->type() == CJToken::Type::Dictionary) {
      CJDictionaryP dict = std::static_pointer_cast<CJDictionary>(evalue_);

      return dict->getProperty(name1);
    }
    else {
      CJObjectTypeP valueType = evalue_->valueType();

      if (! valueType->hasProperty(name1))
        return CJValueP();

      CJValueP propVal = valueType->getProperty(name1);

      CJObjectType::Values values;

      values.push_back(evalue_);

      return valueType->exec(js, name1, values);
    }
  }
  else {
    CJValueP value = js->lookupValue(identifiers_);

    return value;
  }
}

void
CJExecIdentifiers::
print(std::ostream &os) const
{
  int i = 0;

  for (auto &id : identifiers_) {
    if (i > 0)
      os << ".";

    os << id->name();

    ++i;
  }
}
