//============================================================================

#include "FusionPacket.h"
#include "FusionField.h"

//============================================================================

using namespace migme;

//============================================================================

size_t FusionPacket::GetNumberOfFields() const
{
	FusionField* p = (FusionField*) (this+1);
	FusionField* pEnd = (FusionField*) ((char*) (this+1) + contentSize);
	
	size_t count = 0;
	while(p < pEnd)
	{
		++count;
		p = p->GetNextField();
	}
	return count;
}

const FusionField* FusionPacket::GetFieldByIndex(size_t i) const
{
	FusionField* p = (FusionField*) (this+1);
	FusionField* pEnd = (FusionField*) ((char*) (this+1) + contentSize);
	while(p < pEnd)
	{
		if(i == 0) return p;
		p = p->GetNextField();
		--i;
	}
	return nullptr;
}

const FusionField* FusionPacket::GetFieldById(int fieldId) const
{
	FusionField* p = (FusionField*) (this+1);
	FusionField* pEnd = (FusionField*) ((char*) (this+1) + contentSize);
	
	while(p < pEnd)
	{
		if(p->fieldId == fieldId) return p;
		p = p->GetNextField();
	}
	return nullptr;
}

//============================================================================

