
# Custom Functions
.set Reloc,0x800037d0 # r3 xxFunction dat
.set InitRdFunction,0x800037d4 # r3 xxFunction r4 rider id
.set Rider_GetRiderID,0x800037d8 # r3 playerdata out -> r3 becomes rider id
.set Rider_ExecuteRdFunction,0x800037dc # r3 playerdata r4 functionid
.set Menu_SelectRiderLogic,0x800037e0 # 
.set Menu_UpdateColorBox,0x800037e4 # 
.set BP,0x800037e8 # 


# rdFunctionIndices
.set rd_StateLogic, 0
.set rd_OnInit, 1
.set rd_OnInput, 2

# File Structure
.set  Arch_RiderTable,0x04
  .set  Arch_RiderCount,0x00
  .set  Arch_RiderRuntimeSelection,0x04
  .set  Arch_RiderFileStrings,0x08
  .set  Arch_RiderSymbolRuntime,0x0C
  .set  Arch_RiderParams,0x10
  .set  Arch_RiderFunctionRuntime,0x14
.set  Arch_VehicleTable,0x08
  .set  Arch_VehicleMetaData,0x00
  .set  Arch_VehicleArchiveStrings,0x04
  .set  Arch_VehicleArchiveRuntimes,0x08
  .set  Arch_VehicleFunctions1,0x0C
  .set  Arch_VehicleFunctions2,0x10
  .set  Arch_SelectVehicleIDs,0x14
  .set  Arch_SelectVehicle3ByteTable,0x18
  .set  Arch_SelectVehicleSISNameIndex,0x1C
  .set  Arch_SelectVehicleSISDescIndex,0x20
.set Arch_MusicTable,0x10
.set Arch_RiderFunctionTable,0x14
  .set Arch_StateLogicTable,0x00
  
# RAM Pointers


.set OFST_kexPtrStart, -4
.set OFST_VehicleMetadata, OFST_kexPtrStart + 4
.set OFST_VehicleFileStrings, OFST_VehicleMetadata + 4
.set OFST_VehicleArchiveRuntimes, OFST_VehicleFileStrings + 4
.set OFST_VehicleFunctions1, OFST_VehicleArchiveRuntimes + 4
.set OFST_VehicleFunctions2, OFST_VehicleFunctions1 + 4
.set OFST_SelectVehicleIDs, OFST_VehicleFunctions2 + 4
.set OFST_SelectVehicle3ByteTable, OFST_SelectVehicleIDs + 4
.set OFST_SelectVehicleSISNameIndex, OFST_SelectVehicle3ByteTable + 4
.set OFST_SelectVehicleSISDescIndex, OFST_SelectVehicleSISNameIndex + 4
.set OFST_MusicTable, OFST_SelectVehicleSISDescIndex + 4
.set OFST_RiderTable, OFST_MusicTable + 4
.set OFST_RuntimeRiderSelection, OFST_RiderTable + 4
.set OFST_RuntimeRiderSymbols, OFST_RuntimeRiderSelection + 4
.set OFST_RuntimeRiderFunctions, OFST_RuntimeRiderSymbols + 4
.set OFST_RiderParamTable, OFST_RuntimeRiderFunctions + 4
.set OFST_RdFunctionTable, OFST_RiderParamTable + 4
.set OFST_StateLogicTable, OFST_RdFunctionTable + 4
.set OFST_kexData, 0
