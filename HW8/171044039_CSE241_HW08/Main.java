
public class Main
{

	public static void main(String[] args)
	{

		System.out.println("[DEBUG]    Starting to test...    [DEBUG]");

		HashSet<Integer> hashset = new HashSet<Integer>();
		ArrayList<Integer> arraylist = new ArrayList<Integer>();
		LinkedList<Integer> linkedlist = new LinkedList<Integer>();

		hashset.add(5);
		hashset.add(6);
		hashset.add(7);
		hashset.add(8);
		hashset.add(9);
		hashset.add(5);
		hashset.add(5);
		hashset.add(11);

		System.out.println("Hashset>");
		Iterator<Integer> begin = hashset.iterator();
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		if(hashset.contains(5))
			System.out.println("\nHashset contains 5!");

		hashset.remove(5);
		hashset.remove(6);

		System.out.println("5-6 removed from Hashset>");
		begin = hashset.iterator();
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		arraylist.add(3);
		arraylist.add(6);
		arraylist.add(3);
		arraylist.add(6);
		arraylist.add(6);
		arraylist.add(3);
		arraylist.add(11);
		arraylist.add(11);

		System.out.println("\nArrayList>");
		begin = arraylist.iterator();
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		hashset.addAll(arraylist);
		begin = hashset.iterator();
		System.out.println("\nArrayList added into Hashset>");
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		if(hashset.containsAll(arraylist))
			System.out.println("\nHashset contains ArrayList!");

		arraylist.add(12);
		arraylist.add(13);
		arraylist.add(14);
		arraylist.add(15);

		System.out.println("Updated ArrayList>");
		begin = arraylist.iterator();
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		hashset.retainAll(arraylist);
		System.out.println("\nArrayList retained from HashSet>");
		begin = arraylist.iterator();
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		hashset.removeAll(arraylist);
		begin = hashset.iterator();
		System.out.println("\nArrayList removed from Hashset>");
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		linkedlist.add(4);
		linkedlist.add(3);
		linkedlist.add(2);
		linkedlist.add(1);
		linkedlist.add(0);

		begin = linkedlist.iterator();
		System.out.println("\nLinkedList>");
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		linkedlist.addAll(arraylist);
		System.out.println("\nArrayList added into LinkedList>");
		begin = linkedlist.iterator();
		while(begin.hasNext())
		{
			System.out.printf("%s ", begin.next());
		}

		HashSet<String> str_hashset = new HashSet<String>();
		ArrayList<String> str_arraylist = new ArrayList<String>();
		LinkedList<String> str_linkedlist = new LinkedList<String>();

		str_hashset.add("One");
		str_hashset.add("Two");
		str_hashset.add("Three");
		str_hashset.add("Four");
		str_hashset.add("One");
		str_hashset.add("Two");

		str_arraylist.addAll(str_hashset);
		str_linkedlist.addAll(str_hashset);

		str_arraylist.add("Five");
		str_arraylist.add("Six");
		str_arraylist.add("Two");
		str_arraylist.add("Two");

		str_linkedlist.add("Five");
		str_linkedlist.add("Six");

		System.out.println("\nString Hashset>");
		Iterator<String> str_begin = str_hashset.iterator();
		while(str_begin.hasNext())
		{
			System.out.printf("%s ", str_begin.next());
		}
		System.out.println("\nString ArrayList>");
		str_begin = str_arraylist.iterator();
		while(str_begin.hasNext())
		{
			System.out.printf("%s ", str_begin.next());
		}
		System.out.println("\nString LinkedList>");
		str_begin = str_linkedlist.iterator();
		while(str_begin.hasNext())
		{
			System.out.printf("%s ", str_begin.next());
		}



		if(str_linkedlist.contains("Five"))
			System.out.println("\nLinkedList contains 'Five'");

		System.out.println("Size of ArrayList: " + str_arraylist.size());

		if(!str_hashset.isEmpty())
			System.out.println("Hashset is not empty!");

		str_hashset.clear();
		System.out.println("Clearing the Hashset!");
		if(str_hashset.isEmpty())
			System.out.println("Hashset is empty!");

		System.out.println("[DEBUG]    Test is over...    [DEBUG]");


	} 

}