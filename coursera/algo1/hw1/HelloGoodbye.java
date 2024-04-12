public class HelloGoodbye {
    public static void main(String[] args) {
        System.out.println("Hello " + String.join(" and ", args));

        // Say goodbye and then print the arguments in reverse order, separated by
        // "and".
        System.out.print("Goodbye ");
        for (int i = args.length - 1; i >= 0; i--) {
            System.out.print(args[i]);
            if (i > 0) {
                System.out.print(" and ");
            }
        }
        System.out.println();
    }
}