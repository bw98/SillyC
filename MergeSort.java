import java.util.*;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.Future;
import java.util.concurrent.RecursiveTask;

public class MergeSort extends RecursiveTask<Void> {
    int[] intArr;

    public MergeSort(int[] intArr) {
        this.intArr = intArr;
    }

    public void merge(int[] leftArray, int[] rightArray, int[] intList) {
        // i：leftArray数组索引，j：rightArray数组索引，k：intList数组索引

        int i = 0, j = 0, k = 0;
        while (i < leftArray.length && j < rightArray.length) {
            if (leftArray[i] < rightArray[j]) {
                intList[k] = leftArray[i];
                i++;
            } else {
                intList[k] = rightArray[j];
                j++;
            }
            k++;
        }

        // 将还剩余元素没有遍历完的数组直接追加到intArr后面
        if (i == leftArray.length) {
            for (; j < rightArray.length; j++, k++) {
                intList[k] = rightArray[j];
            }
        } else {
            for (; i < leftArray.length; i++, k++) {
                intList[k] = leftArray[i];
            }
        }
    }


    @Override
    protected Void compute() {
        if (intArr.length > 1) {
            int[] leftArray = Arrays.copyOfRange(intArr, 0, (int)(intArr.length / 2));
            int[] rightArray = Arrays.copyOfRange(intArr, (intArr.length / 2), intArr.length);
            invokeAll(new MergeSort(leftArray), new MergeSort(rightArray));
            merge(leftArray, rightArray, intArr);
        }
        return null;
    }


    public static void main(String[] args) {
        ForkJoinPool forkJoinPool = new ForkJoinPool();
        Random random = new Random();
        List<Integer>  intList = new ArrayList<>();
        int tot = 20000000;
        int bound = 2500000;
        for (int i=0; i<tot; i++) {
            intList.add(random.nextInt(random.nextInt()));
        }
        int[] intArr = new int[intList.size()];
        for(int i = 0; i < intList.size(); i++) {
            intArr[i] = intList.get(i);
        }
        long now = System.currentTimeMillis();
        System.out.println("生成随机数所用时间:" + (System.currentTimeMillis() - now));

        MergeSort mergeSort = new MergeSort(intArr);

        Future<Integer> future = forkJoinPool.submit(mergeSort);
        try {
            future.get();
            System.out.println(Arrays.toString(intArr));
            System.out.println("总用时:" + (System.currentTimeMillis() - now));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}

