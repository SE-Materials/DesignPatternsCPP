#include "Policies.h"
#include "Widget.h"

using namespace std;

// ----------------------- Host classes ------------------------------------//
template <typename CreationPolicy>
class CreationManager : public CreationPolicy
{
	void FunctionA()
	{

	}
};



// ----------------------- typedefs ----------------------------------------//

typedef CreationManager<OpNewCreator<Widget>> WidgetManager;



// -------------------------------------------------------------------------//

int main()
{
	return 0;
}
