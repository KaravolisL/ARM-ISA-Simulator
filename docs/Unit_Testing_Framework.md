# Unit Testing Framework

Below is the sequence diagram for the unit testing framework. A test suite is constructed at the beginning. Individual unit tests are added to the suite. These indiviual unit tests are made up of separate test cases (sub tests) that are performed on the class under test. Both the suite and the individual unit tests have setup and teardown functions that can be customized for the purpose of the suite/unit test.

```plantuml
@startuml

participant Main
participant UnitTestSuite as utsuite
participant UnitTest as ut
participant "//ClassUnderTest//" as cut

Main -> utsuite ** : Create
Main -> utsuite : SetSuiteSetup()
loop for each test
Main -> utsuite : AddTest()
end
Main -> utsuite : SetSuiteTeardown()

Main -> utsuite : Run()
activate utsuite

utsuite -> utsuite : SuiteSetup()
loop for each test
utsuite -> ut ** : Create
utsuite -> ut : SetSetup()
loop for each test case
utsuite -> ut : AddSubTest()
end
utsuite -> ut : SetTeardown()
utsuite -> ut : Run()
activate ut
ut -> ut : Setup()
ut -> cut : Perform tests
ut -> ut : Teardown()
return pass/fail
end
utsuite -> utsuite : SuiteTeardown()
return pass/fail

@enduml
```