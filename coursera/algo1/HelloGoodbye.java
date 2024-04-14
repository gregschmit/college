public class HelloGoodbye {
    public static void main(String[] args) {
        System.out.println("Hello " + String.join(" and ", args) + ".");
        System.out.println("Goodbye " + args[1] + " and " + args[0] + ".");
    }
}