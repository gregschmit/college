/**
 * @file
 * Entry point for HW2.  You should not touch this file for your assignment.
 */

import java.util.HashSet;
import java.util.HashMap;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;
import net.sourceforge.argparse4j.impl.Arguments;
import net.sourceforge.argparse4j.ArgumentParsers;
import net.sourceforge.argparse4j.inf.ArgumentParser;
import net.sourceforge.argparse4j.inf.ArgumentParserException;
import net.sourceforge.argparse4j.inf.Namespace;
import cs342.animals.*;

public class Main {

  public static HashSet<Animal> remainingOptions(HashSet<Animal> currentOptions, String methodName, boolean filterOption) {

    HashSet<Animal> filteredAnimals = new HashSet<>();
    boolean testResult;

    for (Animal anAnimal : currentOptions) {
      try {
        Method testMethod = anAnimal.getClass().getMethod(methodName);
        testResult = (boolean) testMethod.invoke(anAnimal);
      } catch (NoSuchMethodException | IllegalAccessException | InvocationTargetException e) {
        continue;
      }

      if (testResult != filterOption) {
        continue;
      }

      filteredAnimals.add(anAnimal);
    }

    return filteredAnimals;
  }

  public static void main(String[] args) {
    
    ArgumentParser parser = ArgumentParsers
      .newArgumentParser("run")
      .defaultHelp(true);
    
    parser.addArgument("--warmblood")
      .type(Arguments.booleanType())
      .required(true);

    parser.addArgument("--underwater")
      .type(Arguments.booleanType())
      .required(true);

    parser.addArgument("--euroname")
      .type(Arguments.booleanType())
      .required(true);

    parser.addArgument("--changecolor")
      .type(Arguments.booleanType())
      .required(true);

    parser.addArgument("--blackandwhite")
      .type(Arguments.booleanType())
      .required(true);

    Namespace res;
    try {
      res = parser.parseArgs(args);
    } catch (ArgumentParserException e) {
      parser.handleError(e);
      return;
    }

    HashSet<Animal> animalTypes = new HashSet<>();
    animalTypes.add(new ShibaInu());
    animalTypes.add(new Chameleon());
    animalTypes.add(new GermanShepard());
    animalTypes.add(new Beluga());
    animalTypes.add(new Orca());
    animalTypes.add(new Snake());

    HashMap<String, Boolean> filterSettings = new HashMap<>();
    filterSettings.put("isWarmBlooded", res.get("warmblood"));
    filterSettings.put("isLivingUnderWater", res.get("underwater"));
    filterSettings.put("isNamedAfterEuropeanCountry", res.get("euroname"));
    filterSettings.put("canChangeColor", res.get("changecolor"));
    filterSettings.put("isBlackAndWhite", res.get("blackandwhite"));
    
    for (String methodName : filterSettings.keySet()) {
      boolean argValue = filterSettings.get(methodName).booleanValue();
      animalTypes = Main.remainingOptions(animalTypes, methodName, argValue);
    }

    int numMatches = animalTypes.size();

    if (numMatches == 0) {
      System.out.println("Unable to find any animals in the system that matched this critera.");
    } else if (numMatches > 1) {
      System.out.println("Seems like multiple animals in the system matched this critera.  Thats odd…");
      for (Animal anAnimal : animalTypes) {
        System.out.printf(" - %s\n", anAnimal.getName());
      }
    } else {
      Animal matchingAnimal = animalTypes.toArray(new Animal[1])[0];
      System.out.println(matchingAnimal.getName());
    }
  }
}