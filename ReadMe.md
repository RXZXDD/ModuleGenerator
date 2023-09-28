# How to Use?
## *Way-1*: 

1.Build project. 

2.Run .exe in console like: 
```batch
	ModuleGenerator.exe ModuleName=[YourModuleName] Path=[Your New Module Path]

 	i.e. ModuleGenerator.exe ModuleName=TestD Path=E:\UEProject\PakTest\Plugins\ComputeShaderTestPlugin\Source
``` 

 --- 
 ## *Way-2(having some issue,working on)*: 

  1.Install Setup.exe 

  2.Go to the Install folder Find Env.bat  

  3.Run the batch 
  
  <font color="Red">Just Add  install path to system environment variables, so Check system environment variables PATH contains the install path or not, 
  
  if not pleae add it manually</font> 

  later will fixed this problem (maybe)

  4.Run .exe in PowerShell like: 
  ```
	ModuleGenerator.exe ModuleName=[YourModuleName] Path=[Your New Module Path]

 	i.e. ModuleGenerator.exe ModuleName=TestD Path=E:\UEProject\PakTest\Plugins\ComputeShaderTestPlugin\Source
 ``` 
   ---
  <br>
 <br>
 <br>

# TODO List
1. auto add system enviroment value when install


  ---
  <br>
 <br>
 <br>

  # Require doc
## 1.input
- 1-1 [ModuleName]

- 1-2 [Path] 

        输入插件根文件夹路径 

        E:\UEProject\[YourProject]\Plugins\[PlguinName]

## 2.Output
- 2-1 **NewBlankModule** 

        Locate at: E:\UEProject\[YourProject]\Plugins\[PlguinName]\Source\[ModuleName] 

- 2-2 **Folder Tree** 

        E:\UEProject\[YourProject]\Plugins\[PlguinName]\Source\[ModuleName]
        |
        |-Private
            |-[ModuleName].cpp
        |-Public
            |- [ModuleName].h
        |-[ModuleName].Build.cs 

## 3.Content

### 3-1 [ModuleName].Build.cs 

```c++

using UnrealBuildTool;

public class [ModuleName] : ModuleRules
{
	public [ModuleName](ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine", 
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}

```
  
 ### 3-3 [ModuleName].h

 ```c++
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"


class F[ModuleName]Module : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

 ``` 
  




 ### 3-3 [ModuleName].cpp

 ```c++
 // Copyright Epic Games, Inc. All Rights Reserved.

#include "[ModuleName].h"

#define LOCTEXT_NAMESPACE "F[ModuleName]"

void F[ModuleName]Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void F[ModuleName]Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(F[ModuleName]Module, [ModuleName])
 ```
