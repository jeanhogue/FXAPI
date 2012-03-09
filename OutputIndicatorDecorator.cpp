#include "OutputIndicatorDecorator.h"


OutputIndicatorDecorator::OutputIndicatorDecorator(IFXIndicator *_decoree, const std::string &outFilename)
{
    decoree = _decoree;
    out.open(outFilename.c_str());
}

OutputIndicatorDecorator::~OutputIndicatorDecorator()
{
    out.close();
}

void OutputIndicatorDecorator::OnNewBar(double sample)
{
    decoree->OnNewBar(sample);
    out << decoree->GetValue() << std::endl;
}