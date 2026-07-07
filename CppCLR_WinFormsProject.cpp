#include "pch.h"
#include "Form1.h"

using namespace System;

// int main(array<System::String ^> ^args)
#include <cstdlib>
#include <ctime> 

using namespace Caballos;

int main() {
	srand(time(nullptr));
	Application::Run(gcnew MyForm());
	return 0;
}