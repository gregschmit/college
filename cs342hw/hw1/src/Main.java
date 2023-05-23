/**
 * @file
 * Skeleton code for the first homework assignment for CS 342.
 */

import java.util.*;
import java.text.SimpleDateFormat;

// You can import any libraries from the standard library you'd like.  No
// third party code is allowed.

public class Main {
  public static void main(String[] args) {

    System.out.println("Just about to get started…");

    // First, write some code below that prints your email address out to
    // the commandline / standard out
    
    System.out.println("gschmi4@uic.edu");

    // Second, create a variable, called `qTwoInt` of type `int` with
    // the value of 3.  Then, create a second variable, `qTwoInteger`, of type
    // `Integer`, using the value of the `qTwoInt` variable.  Then, create
    // a variable called `qTwoString`, of type `String`, that contains the
    // string value of this integer, as converted from the `qTwoInteger`
    // (e.g. do *not* hard code the value of `qTwoString` into your program).
    // Print out the string value.

    int qTwoInt = 3;
    Integer qTwoInteger = new Integer(qTwoInt);
    String qTwoString = new String(qTwoInteger.toString());
    System.out.println(qTwoString);

    // Third, define an array of Strings below, containing each part of your
    // name.  For example, if Mary Tyler Moore was completing this assignment,
    // she'd want an array of length three, containing the strings "Mary",
    // "Tyler" and "Moore".

    String[] myName = { "Gregory", "Nathan", "Schmit" };

    // Then, iterate over this array, and print your name back out, but
    // with "_" (underscores) separating each part of your name.  In the case
    // of Mary Tyler Moore, the string "Mary_Tyler_Moore" would be printed.
    // Write code that accomplishes this below.

    Iterator<String> it = Arrays.asList(myName).iterator();
    if (it.hasNext()) {
        String part = it.next();
        System.out.print(part);
        while (it.hasNext()) {
            part = it.next();
            System.out.print("_" + part);
        }
        System.out.print("\n");
    }

    // Fourth, write code that finds the current date, and prints the date out
    // in the following format: YYYY-MM-DD

    Date today = new Date();
    String today_s = new SimpleDateFormat("yyyy-MM-dd").format(today);
    System.out.println(today_s);

    // Fifth, write code below that looks up and prints out the current version
    // of Java.  This should look something like 1.8.0_131 (though will
    // of course differ slightly depending on your setup).  Tip: If you're using
    // the right method(s), you will not need to do any formatting to get
    // your solution to match.
    
    System.out.println(System.getProperty("java.version"));
  }
}
