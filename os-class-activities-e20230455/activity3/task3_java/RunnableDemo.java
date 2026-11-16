class Task implements Runnable {
    private final String taskName;

    public Task(String name) {
        this.taskName = name;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 3; i++) {
            System.out.println(taskName + " - Step " + i);

            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println(taskName + " interrupted.");
                return;
            }
        }
    }
}

public class RunnableDemo {
    public static void main(String[] args) {
        Thread t1 = new Thread(new Task("Download"));
        Thread t2 = new Thread(new Task("Process"));
        Thread t3 = new Thread(new Task("Upload"));

        t1.start();
        t2.start();
        t3.start();

        try {
            t1.join();
            t2.join();
            t3.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("All tasks completed.");
    }
}

