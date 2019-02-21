#include "HashSet.cpp"
#include "ArrayList.cpp"
#include "LinkedList.cpp"
#include "Iterator.cpp"
#include <iostream>
#include <string>
#include <list>
#include <set>

using namespace ozmekik_collection;
using std::cout;
using std::endl;



int main()
{
	LinkedList<int> linkedlist;
	ArrayList<int> arraylist;
	HashSet<int> hashset;

	LinkedList<std::string, std::list<std::string>> str_linkedlist;
	ArrayList<std::string, std::list<std::string>> str_arraylist;
	HashSet<std::string, std::list<std::string>>    str_hashset;

	linkedlist.add(5);
	linkedlist.add(5);
	linkedlist.add(8);
	linkedlist.add(9);
	linkedlist.add(1);
	linkedlist.add(2);
	linkedlist.add(3);
	linkedlist.add(5);

	arraylist.addAll(linkedlist);
	hashset.addAll(linkedlist);

	arraylist.add(7);
	arraylist.add(6);

	cout<<"[DEBUG] Starting to test..."<<endl;

	cout<<"Hashset>> ";
	for_each(hashset.iterator(),[](int e){cout<<e<<" ";}); cout<<endl; 
	cout<<"ArrayList>> ";
	for_each(arraylist.iterator(),[](int e){cout<<e<<" ";}); cout<<endl;
	cout<<"LinkedList>> ";
	for_each(linkedlist.iterator(),[](int e){cout<<e<<" ";}); cout<<endl;

	if(hashset.contains(5)) 
		cout<<"Hashset contains 5!"<<endl;
	if(linkedlist.contains(3)) 
		cout<<"LinkedList contains 3!"<<endl;
	if(arraylist.contains(2)) 
		cout<<"Arraylist contains 2!"<<endl;


	if(linkedlist.containsAll(hashset))
		cout<<"Linkedlist contains HashSet!"<<endl;

	if(!(hashset.isEmpty()))
		cout<<"Hashset is not empty!"<<endl;

	arraylist.remove(3);
	arraylist.remove(7);
	arraylist.remove(5);
	arraylist.remove(8);
	arraylist.remove(6);
	hashset.removeAll(arraylist);
	linkedlist.removeAll(arraylist);
	hashset.add(1);

	cout<<"[DEBUG] removeAll() test: "<<endl;
	cout<<"Hashset>> ";
	for_each(hashset.iterator(),[](int e){cout<<e<<" ";}); cout<<endl; 
	cout<<"ArrayList>> ";
	for_each(arraylist.iterator(),[](int e){cout<<e<<" ";}); cout<<endl;
	cout<<"LinkedList>> ";
	for_each(linkedlist.iterator(),[](int e){cout<<e<<" ";}); cout<<endl;


	arraylist.add(5);
	arraylist.add(5);
	arraylist.add(9);
	arraylist.add(3);	
	linkedlist.addAll(arraylist);

	hashset.retainAll(linkedlist);
	hashset.retainAll(arraylist);

	cout<<"[DEBUG] RetainAll() Test: "<<endl;
	cout<<"Hashset>> ";
	for_each(hashset.iterator(),[](int e){cout<<e<<" ";}); cout<<endl; 
	cout<<"ArrayList>> ";
	for_each(arraylist.iterator(),[](int e){cout<<e<<" ";}); cout<<endl;
	cout<<"LinkedList>> ";
	for_each(linkedlist.iterator(),[](int e){cout<<e<<" ";}); cout<<endl;



	str_arraylist.add("one");
	str_arraylist.add("two");
	str_arraylist.add("three");
	str_arraylist.add("four");
	str_arraylist.add("four");
	str_arraylist.add("five");
	str_arraylist.add("three");
	str_arraylist.add("one");

	str_linkedlist.addAll(str_arraylist);
	str_hashset.addAll(str_arraylist);


	cout<<"String Hashset>> ";
	for_each(str_hashset.iterator(),[](std::string e){cout<<e<<" ";}); cout<<endl;
	cout<<"String Arraylist>> ";
	for_each(str_arraylist.iterator(),[](std::string e){cout<<e<<" ";}); cout<<endl; 
	cout<<"String LinkedList>> ";
	for_each(str_linkedlist.iterator(),[](std::string e){cout<<e<<" ";}); cout<<endl;

	cout<<"[DEBUG] QUEUE poll() Test:"<<endl;
	cout<<"Head of Queue: "<<str_linkedlist.poll()<<endl;
	cout<<"String LinkedList>> ";
	for_each(str_linkedlist.iterator(),[](std::string e){cout<<e<<" ";}); cout<<endl;

	try
	{
		str_linkedlist.clear();
		auto e = str_linkedlist.element();

	}

	catch(empty_queue &e)
	{	
		cout<<"Error occured: "<<e.what()<<endl;
	}


	auto it1 = arraylist.iterator();
	auto it2 = hashset.iterator();

	hashset.addAll(arraylist);

	cout<<"ArrayList Iterator Testing:"<<endl;
	while(it1.hasNext())
	{
		cout<<it1.next()<<" ";
	}

	cout<<endl<<"Hash Iterator Testing:"<<endl;
	while(it2.hasNext())
	{
		cout<<it2.next()<<" ";
	}

	try
	{
		auto it3 = linkedlist.iterator();
		it3.remove();
		
	}

	catch(bad_iter &e)
	{
		cout<<endl<<"Error occured: "<<e.what()<<endl;
	}


	cout<<"[DEBUG] Test is done!."<<endl;

	return 0;
}