# Instruction Execution

```plantuml
@startuml

participant Process
participant InstructionBuilder as IB
participant InstructionDictionary as ID


Process -> IB: pInstructionBase = BuildInstruction(instruction)

opt instruction[0] == 'B'

IB -> IB

end


@enduml
```

Steps to determining instruction type: \
1. Check if first letter is B
2. If so, compare against BIC, BLX, BX
