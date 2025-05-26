public class Book
{
    private string title;
    private string author;
    private string ISBN;
    public Book(string title, string author, string ISBN)
    {
        this.title = title;
        this.author = author;
        this.ISBN = ISBN;
    }

    public string getTitle() { return title; }

    public string getAuthor() { return author; }

    public string getISBN() { return ISBN; }
}

public class Member
{
    private string name;
    private string id;
    private string address;
    private string phone;
    private int borrowedBookCount;
    private int borrowedBookLimit;
    private List<Book> borrowedBooks;
    public Member(string name, string id, string address, string phone)
    {
        this.name = name;
        this.id = id;
        this.address = address;
        this.phone = phone;
        borrowedBookCount = 0;
        borrowedBookLimit = 5;
        borrowedBooks = new List<Book>();
    }

    public string getId() { return id; }

    public int getBorrowedBookCount() { return borrowedBookCount; }

    public int getBorrowedBookLimit() { return borrowedBookLimit; }

    public void incrementBBC() { borrowedBookCount++; }

    public void decrementBBC() { borrowedBookCount--; }

    public addBookToBorrowedBooks(Book book) {
        borrowedBooks.Add(book);
    }

    public List<Book> getBorrowedBookList() {
        return borrowedBooks;
    }
}

public enum TransactionType {
    BORROW,
    RETURN
}

public class Transaction
{
    private Member member;
    private Book book;
    private TransactionType tt;
    public Transaction (Member member, Book book, TransactionType tt)
    {
        this.member = member;
        this.book = book;
        this.tt = tt;
    }

    public Member getMember() {
        return member;
    }
}

public class BookInventory
{
    private int totalCopies;
    private int availableCopies;
    private Book book;

    public BookInventory(int totalCopies, Book book)
    {
        this.totalCopies = totalCopies;
        this.book = book;
        this.availableCopies = totalCopies;
    }

    public int getTotalCopies() { return totalCopies; }
    
    public void setTotalCopies(int cnt) { totalCopies = cnt; }

    public int getAvailableCopies() { return availableCopies; }

    public void setAvailableCopies(int cnt) { availableCopies = cnt; }

    public void incrementAC() { 
        if (availableCopies < totalCopies) 
            availableCopies++; 
    }
    
    public void decrementAC() { availableCopies--; }

    public Book getBook() { return book; }
}

public interface ILibrary 
{
    void AddBook(Book book);
    bool BorrowBook(string ISBN);
    bool ReturnBook(Book book);
    List<BookInventory> SearchBookByTitle(string title);
    List<BookInventory> SearchBookByAuthor(string author);
    BookInventory SearchBookByISBN(string ISBN);
    void RegisterMember(Member member);
    List<Transaction> GetBorrowingHistory(string userId);
}

public class Library : ILibrary
{
    // private Dictionary<string, Book> books;
    private Dictionary<string, BookInventory> books;
    private Dictionary<string, Member> members;
    private List<Transaction> transactions;
    public Library()
    {
        books = new Dictionary<string, BookInventory>();
        members = new Dictionary<string, User>();
        transactions = new List<Transaction>();
    }

    void RegisterMember(Member member)
    {
        if (!members.ContainsKey(member.getId())) {
            members.Add(member.getId(), member);
        } else {
            // Add a log here that member is already registered.
        }
    }

    public void AddBook(Book book, int count)
    {
        if (!books.ContainsKey(book.getISBN()))
        {
            BookInventory BI = new BookInventory(count, book);
            books.Add(book.getISBN(), BI);
        }
        else {
            BookInventory existingBI = books[book.getISBN()];
            existingBI.setTotalCopies(existingBI.getTotalCopies() + count);
            existingBI.setAvailableCopies(existingBI.getAvailableCopies() + count);
        }
    }

    public bool BorrowBook(string ISBN, Member member)
    {
        // Check if a book with given ISBN exists and available
        BookInventory x = SearchBookByISBN(ISBN);
        
        if (x == null)
            return false; 

        // Check if the member is registered
        Member member = SearchMemberById(member.getId());

        if (member == null)
            return false; // member is not registered

        if (member.getBorrowedBookCount == member.getBorrowedBookLimit) {
            // Member already hits the limit
            return false;
        }
        
        lock (x) {
            if (x.getAvailableCopies() == 0) {
                return false;
            }

            x.decrementAC();

            // Member borrowed the book, increase the borrow book count
            member.incrementBBC();

            // Add this bool to the list of borrowed books
            member.addBookToBorrowedBooks(x.getBook());

            // Add a transaction
            Transaction t = new Transaction(member, x.getBook(), TransactionType.BORROW);
            transactions.Add(t);

            return true;
        }
    }

    public bool ReturnBook(Book book, Member member)
    {
        BookInventory x = SearchBookByISBN(book.getISBN());
        
        if (x == null)
            return false; // Book does not exist

        // Check if the member is registered
        Member member = SearchMemberById(member.getId());

        if (member == null)
            return false; // member is not registered

        lock (x) {
            x.incrementAC();

            // deacrese the borrowedBook count for member
            member.decrementBBC();

            // remove this book from borrowed books of member
            for (int i=0;i<member.getBorrowedBookList().Count;i++) {
                if (member.getBorrowedBookList()[i].getISBN() == book.getISBN()) {
                    member.getBorrowedBookList().RemoveAt(i);
                }
            } 

            // Add a transaction
            Transaction t = new Transaction(member, book, TransactionType.RETURN);
            transactions.Add(t);

            return true;
        }
    }

    public List<BookInventory> SearchBookByTitle(string title)
    {
        List<BookInventory> x = new List<BookInventory>();
        foreach(var book in books)
        {
            if (book.Value.getBook().getTitle() == title)
                x.Add(book.Value);
        }
        return x;
    }

    public List<BookInventory> SearchBookByAuthor(string author)
    {
        List<BookInventory> x = new List<BookInventory>();
        foreach(var book in books)
        {
            if (book.Value.getBook().getAuthor() == author)
                x.Add(book.Value);
        }
        return x;
    }

    public BookInventory SearchBookByISBN(string ISBN)
    {
        books.TryGetValue(ISBN, out BookInventory x);
        return x;
    }

    public Member SearchMemberById(string id) {
        members.TryGetValue(id, out Member x);
        return x;
    }

    public List<Transaction> GetBorrowingHistory(string memberId)
    {
        List<Transaction> ans = new List<Transaction>();

        // Check if the member is registered
        Member member = SearchMemberById(memberId);

        if (member == null)
            return ans; // member is not registered

        foreach (var tran in transactions) {
            if (tran.getMember().getId() == memberId) {
                ans.Add(tran);
            }
        }

        return ans;
    }
}
