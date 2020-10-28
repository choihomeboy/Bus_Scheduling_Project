# Release_notes

## Refactoring
- Refactoring (1 and 2) is implemented in the branch refactor/iter3 to prevent for the unmatching structure or names with the tests built by CSCI3081w faculties.
- We, developers in the class, have to be tested by a same test, master branch contains in strict structure.
- Instruction to access the branch for the users without experience of github.


### Refactoring 1
- Refactoring 1 handles the situation which people are generated in the
end of the route because people generated in last stop of the route does not have anywhere to go. In my drivers, I set them as 0 and strict it to be 0 with the comment, but it is for the users who want their own simulator. And in furthermore situation, you can never make passengers at the stop with passenger generating probability equals to 0. I modified the passenger_generator.cc. The passenger_generator.cc deletes the last probability in the list, which is probability for last stop of the route, and add 0 into the list.

### Refactoring 2
I took care of two methods for code readability. The explanation document is placed in the project/docs, and filename is refactor.pdf

## Regression Tests
For regression tests, the goal is to verify that features that worked once stay working, even as you continue to add to the code. For regression tests, r_local_simulator(.cc and .h), rtest_passenger_generator(.cc and .h), passenger_factory.cc which generate the passenger not randomly so that we can compare the outputs. Hard coded regression test is provided and the faster version of the regression test is provided as well by making route shorter.

### Environment
Make sure to uncomment following lines
- line 17
- line 65
- line 67
- line 69~71
- line 78
- line 82
- line 84~88
> When you are done with regression test, make sure to comment those lines
> to randomly generate the passengers

This makes the PassengerGenerator to not randomly generate the passengers.
#### Base version of regression test
In project/src folder,
> make regression_test <br>
> ../build/bin/regression_test <output_file1> <br>
> ../build/bin/regression_test <output_file2> <br>
> diff output_file1 output_file2 <br>

#### Faster version of regression test
In project/src folder,

> make faster_regression_test <br>
> ../build/bin/faster_regression_test <output_file1> <br>
> ../build/bin/faster_regression_test <output_file2> <br>
> diff output_file1 output_file2 <br>

** If two outputs are same, nothing will show up in terminal. Otherwise,
you fail the regression_test. Further tests are required in that case.**
