#include <iostream>

using namespace std;

#include <AK/AkWwiseSDKVersion.h>

int main()
{
	cout << "Wwise Version: "<< AK_WWISESDK_VERSION_MAJOR << "." << AK_WWISESDK_VERSION_MINOR << "." << AK_WWISESDK_VERSION_SUBMINOR << "." << AK_WWISESDK_VERSION_BUILD;
	cin.get();
}