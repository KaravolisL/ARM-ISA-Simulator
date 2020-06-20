# Process Initialization

The process initialization procedure occurs at startup of the program. Using the file name provided by the user, a Process object is constructed. The main file and each additional included file are read. Information such as labels, static memory, and constants are initialized within the Process object itself. After returning from the `Initialize` method, the Process is ready for execution.


```plantuml
@startuml

participant Main as main
participant Process as proc
participant ProcessInitializer as PI
participant "Io::FileIterator" as FI
participant "Io::LineParser" as LP

main -> proc ** : construct
main -> proc : Initialize(fileName)
activate proc
proc -> PI ** : construct(this)
proc -> PI : Initialize(fileName)
activate PI
PI -> PI : InitializeFile(fileName)
activate PI
PI -> FI ** : construct(fileName)

loop while fileIterator.HasNext()

PI -> LP ** : construct
PI -> LP : GetLineType
PI -> PI : Line Specific Actions

end

return

PI -> proc : Set PC
PI -> proc : Set File Iterator
PI -> proc : Set SP

return
return 


@enduml
```