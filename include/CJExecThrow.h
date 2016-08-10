#ifndef CJExecThrow_H
#define CJExecThrow_H

#include <CJToken.h>
#include <iostream>

// throw <expression>
class CJExecThrow : public CJToken {
 public:
  CJExecThrow();

  void setExpression(CJExecExpressionP expr) {
    expr_ = expr;
  }

  CJValueP exec(CJavaScript *js) override;

  void print(std::ostream &os) const override;

 private:
  CJExecExpressionP expr_;
};

typedef std::shared_ptr<CJExecThrow> CJExecThrowP;

#endif
