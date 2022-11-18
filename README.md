# 2023-emiris-k23-assignment-1

*Project Παραδοτέο 1*

Ομάδα:

Άγγελος Κορακίτης ΑΜ 1115201900087 (sdi1900087)
Σταύρος Τρουπής ΑΜ 1115201900191 (sdi1900191)

Έχουν υλοποιηθεί οι αλγόριθμοι 1 και 2 της εκφώνησης, ο αυξητικός και με βάση το κυρτό περίβλημα.

Ο Άγγελος (sdi1900087) ασχολήθηκε με την υλοποίηση του αυξητικού αλγόριθμου.
Ο Σταύρος (sdi1900191) ασχολήθηκε με την υλοποίηση του αλγόριθμου με βάση το κυρτό περίβλημα.

Περιεχόμενα README:
-   Kατάλογος αρχείων.
-   Περιγραφή αρχείων.
-   Οδηγίες μεταγλώττισης και χρήσης του προγράμματος.
-   Περιγραφή κώδικα.
-   Παραδείγματα εκτέλεσης και σχολιασμός τους.

-   Κατάλογος αρχείων:
.
├── build
│   └── CMakeFiles
│      
├── include
│    ├── Polygonization_Using_Convex_Hull_Algorithm.hpp
│    ├── Polygonization_Using_Incremental_Algorithm.hpp
│    └── Utilities.hpp
│       
├── modules
│    ├── Polygonization_Using_Convex_Hull_Algorithm.cpp
│    ├── Polygonization_Using_Incremental_Algorithm.cpp
│    └── Utilities.cpp
└── programs
     ├── CMakeLists.txt
     └── main.cpp


-   Περιγραφή αρχείων:

    Η δομή των αρχείων είναι αυτή που φαίνεται στο παραπάνω δέντρο. Στο αρχείο build περιέχονται τα CMakeFiles, εκεί γίνεται και η μεταγλώττιση του
    προγράμματος με τη χρήση της εντολής make. Στην συνέχεια περιέχονται τα include και modules τα οποία περιέχουν τον κώδικα που γράψαμε για την υλοποίηση των αλγορίθμων. Στο αρχείο include, 
    όπως φανερώνει και το όνομα του, περιέχονται τα .hpp αρχεία, τα οποία με την σειρά τους περιέχουν τις δηλώσεις των συναρτήσεων και μια περιγραφή για το τι κάνει η κάθεμια.
    Πιο συγκεκριμένα στο include: 
        -   Polygonization_Using_Convex_Hull_Algorithm.hpp : Περιέχει τις δηλώσεις των συναρτήσεων που χρειάστηκαν για την υλοποίηση του αλγορίθμου με βάση το κυρτό περίβλημα.
        -   Polygonization_Using_Incremental_Algorithm.hpp : Περιέχει τις δηλώσεις των συναρτήσεων που χρειάστηκαν για την υλοποίηση του αυξητικού αλγορίθμου. 
        -   Utilities.hpp : Περιέχει τις δηλώσεις βοηθητικών συναρτήσεων που που δεν σχετίζονται άμεσα με τους αλγόριθμους που υλοποιήθηκαν. Αυτές είναι printing functions που χρησιμοποιήσαμε
        κατα την υλοποίηση των αλγορίθμων για έλεγχο των πολυγώνων, καθώς και των συναρτήσεων για την ανάγνωση από το αρχείο εισόδου, των σημείων, αλλα και το γράψιμο των αποτελεσμάτων σε
        αρχείο εξόδου, σύμφωνα με την εκφώνηση. Επίσης, στο συγκεκριμένο αρχείο υπάρχουν οι δηλώσεις των βιβλιοθηκών που χρειαστήκαμε, όπως επίσης και μερικά typedefs για την αναγνωσιμότητα του κώδικα.
    Στο αρχείο modules περιέχονται τα αντίστοιχα των παραπάνω αρχείων επικεφαλίδας, .cpp αρχεία, με σχολιασμό για την λειτουργία της κάθε συνάρτησης που περιέχεται.
    Πιο συγκεκριμένα στο modules: 
        -   Polygonization_Using_Convex_Hull_Algorithm.cpp
        -   Polygonization_Using_Incremental_Algorithm.cpp
        -   Utilities.cpp
    Τέλος, υπάρχει ο κατάλογος programs που περιέχει το main.cpp, όπου γίνεται μια επεξεργασία των παραμέτρων εισόδου και καλούνται οι απαραίτητες συναρτήσεις από τα αρχεία που περιγράφηκαν παραπάνω για την εκτέλεση των αλγορίθμων σύμφωνα με τις οδηγίες της εκφώνησης, όπως επίσης και το αρχείο CMakeLists.txt το οποίο έχει τις απαραίτητες πληροφορίες για το πρόγραμμα μας, προκειμένου να μπορεί
    να τρέχει το cmake και να δημιουργήσει το απαραίτητο MakeFile για την μεταγλώττιση του προγράμματος.


-   Οδηγίες μεταγλώττισης και χρήσης του προγράμματος:

    Στον κατάλογο /programs εκτελούμε:
    cmake -DCMAKE_BUILD_TYPE=Release -S . -B ../build

    Για να κάνω compile και run εκτελούμε στον κατάλογο /build:
    make
    ./to_polygon -i <point set input file> -o <output file> -algorithm <incremental or convex_hull> -edge_selection <1 or 2 or 3> -initialization <1a or 1b or 2a or 2b | μόνο στον αυξητικό αλγόριθμο>

    (ΠΡΟΣΟΧΗ! Αν ακολουθηθούν τις παραπάνω οδηγίες, για να γίνει η μεταγλώττιση πρέπει να βρίσκεστε στον κατάλογο /build καθώς εκεί περιέχεται το MakeFile και δημιουργείται το εκτελέσιμο to_polygon. Χρειάζεται να λαμβάνετε υποψιν σας και στον προσδιορισμό του input και output file.)


-   Περιγραφή κώδικα:

Όσον αφορά τον Αυξητικό Αλγόριθμο:

Περιγραφή:
    Αρχικά, 
    (a) διατάσσουμε τα σημεία σύμφωνα με την αρχικοποίηση που μας δίνεται σαν παράμετρο κατά την εκτέλεση του προγράμματος. Επιλέγουμε
    τα πρώτα τρία με τη διατεταγμένη σειρά που βρίσκονται στον πίνακα και δημιουργούμε ένα πολύγωνο με αυτά. Αν αυτά είναι συνευθειακά τότε προσθέτουμε ένα ακόμα σημείο
    πριν από το πρώτο. Αν το πολύγωνο δεν είναι counter-clock-wise oriented τότε το κάνουμε. 
    (b)Στη συνέχεια, κάνουμε μια επανάληψη για όλα τα σημεία. 
    Πιο συγκεκριμένα, (b1) για κάθε σημείο βρίσκουμε τις κόκκινες ακμές, δηλαδή αυτές που είναι ορατές από το σημείο που θέλουμε να προσθέσουμε, στο ΚΠ του πολυγώνου. Aυτό γίνεται με τη
    χρήση της συνάρτησης is_edge_visible(), η οποία χρησιμοποιεί την CGAL::intersection() όπου για κάθε ακμή του πολυγώνου και για το τρίγωνο που δημιουργείται απο το σημείο που θέλουμε να προσθέουμε και τα άκρα της ακμής που χρειάζεται να δούμε αν είναι ορατή, βλέπουμε αν υπάρχει τομή με την τρέχουσα πολυγωνική γραμμή.
    (b2) Έπειτα, βρίσκουμε τις ορατές ακμές του πολυγώνου. Αυτές θα βρίσκονται πίσω από τις κόκκινες για αυτόν τον λόγο, για κάθε μια κόκκινη ακμή, ελέγχουμε τις ακμές του πολυγώνου που βρίσκονται ανάμεσα στα δύο άκρα της κόκκινης ακμής, αν αυτές είναι ορατές από το σημείο. Όπως και στο προηγούμενο βήμα γίνεται χρήση της is_edge_visible().
    (b3) Τέλος, επιλέγουμε μια από τις ορατές ακμές του πολυγώνου σύμφωνα με την στρατηγική (τυχαία, ελάχιστη επιφάνεια, μέγιστη επιφάνεια) που μας δώθηκε ως παράμετρος στην εκτέλεση του προγράμματος. 

    Για μεγαλύτερη λεπτομέρεια, υπάρχει εκτενής σχολιασμός στις ίδιες τις συναρτήσεις, στο Polygonization_Using_Incremental_Algorithm.cpp αρχείο.

Όσον αφορά τον Αλγόριθμο με Βάση το Κυρτό Περίβλημα:

Περιγραφή:

    Αρχικά, δημιουργείται το Κυρτό Περίβλημα με τη βοήθεια έτοιμης συνάρτησης της CGAL. Τα εσωτερικά σημεία
    αποθηκεύνται σε ένα πίνακα. Έπειτα, όσο υπάρχουν ακόμα εσωτερικά σημεία, επαναλαμβάνονται τα παρακάτω βήματα:
    - Επιλογή ακμής (ανάλογα με την είσοδο: τυχαία, με ελαχιστοποίηση ή μεγιστοποίηση εμβαδού).
    - Εύρεση του κοντινότερου σημείου απ' όπου υπάρχει ορατότητα.
    - Πρόσθεση του σημείου αυτού στο Πολύγωνο/Πολυγωνική Γραμμή. Σπάμε την ακμή που επιλέξαμε στο πρώτο βήμα 
    και προσθέτουμε δύο ακμές που ενώνουν τα άκρα της αρχικής ακμής με το καινούριο σημείο. 
    - Αφαίρεση του σημείου από το σύνολο των εσωτερικών σημείων.

Σημειώσεις:

    Όσον αφορά την εύρεση του κοντινότερου σημείου:
    Το "κοντινότερο" σημείο από την ακμή θεωρούμε ότι είναι το σημείο το οποίο βρίσκεται πιο κοντά στην ακμή, υπάρχει ορατότητα
    από το σημείο στην ακμή, και η πρόσθεση του σημείου στην πολυγωνική γραμμή δεν θα καθιστά άλλα σημεία εξωτερικά. 

    Όσον αφορά την επιλογή της ακμής:
    --> Όταν έχει δωθεί στην είσοδο η επιλογή 1, επιλέγεται μία τυχαία ακμή της πολυγωνικής ακμής που υπάρχει "κοντινότερο" σημείο προς αυτήν.
    --> Όταν έχει δωθεί στην είσοδο η επιλογή 2, ελέγχονται όλα τα τρίγωνα που δημιουργούνται από τις ακμές της
    πολυγωνικής ακμής και τα "κοντινότερα" σε αυτές σημεία και μετράται το εμβαδό τους. Τελικά επιλέγεται η ακμή που το αντίστοιχο
    τρίγωνό της έχει το ΜΕΓΑΛΥΤΕΡΟ εμβαδό. Αφού στη είσοδο ζητάται η ακμή που προσθέτει το ελάχιστο εμβαδό, αντίστοιχα σε αυτόν τον
    αλγόριθμο επιλέγεται η ακμή που ΑΦΑΙΡΕΙ από το Κυρτό Περίβλημα το μεγαλύτερο εμβαδό. 
    --> Όταν έχει δωθεί στην είσοδο η επιλογή 3, όμοια με το δύο, επιλέγεται η ακμή που το αντίστοιχο τρίγωνό της έχει το ΜΙΚΡΟΤΕΡΟ
    εμβαδό, αφού αφαιρεί απ' το κυρτό πολύγωνο το μικρότερο εμβαδό.

-   Παραδείγματα εκτέλεσης και σχολιασμός τους:

Η μορφή των παραδειγμάτων είναι:
<εντολή εκτέλεσης>
<αποτέλεσμα εξόδου>

Παραδείγματα με τον αλγόριθμο με βάση το κυρτό περίβλημα.

./to_polygon -i ../instances/data/images/us-night-0000300.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 1

Algorithm:convex_hull_edge_selection1
area: 52162590
ratio: 0.450821
construction time: 24.399

./to_polygon -i ../instances/data/images/us-night-0000090.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 2

Algorithm:convex_hull_edge_selection2
area: 24712514
ratio: 0.273234
construction time: 11.638

./to_polygon -i ../instances/data/images/euro-night-0000100.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 2

Algorithm:convex_hull_edge_selection2
area: 18441130
ratio: 0.244309
construction time: 16.265

./to_polygon -i ../instances/data/images/euro-night-0000200.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 2  

Algorithm:convex_hull_edge_selection2
area: 17217062
ratio: 0.222657
construction time: 223.203

./to_polygon -i ../instances/data/images/paris-0000200.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 1

Algorithm:convex_hull_edge_selection1
area: 148970130
ratio: 0.547389
construction time: 5.708

./to_polygon -i ../instances/data/images/paris-0000200.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 3

Algorithm:convex_hull_edge_selection3
area: 242592482
ratio: 0.891403
construction time: 209.158

./to_polygon -i ../instances/data/uniform/uniform-0000070-1.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 3

Algorithm:convex_hull_edge_selection3
area: 13910620
ratio: 0.892392
construction time: 5.273

./to_polygon -i ../instances/data/uniform/uniform-0000100-2.instance -o ../programs/blah.txt -algorithm convex_hull -edge_selection 3

Algorithm:convex_hull_edge_selection3
area: 25964820
ratio: 0.884023
construction time: 19.913

Τα αποτελέσματα είναι αυτά που περιμέναμε. Όσον αφορά την επιφάνεια του πολυγώνου, το ratio είναι υψηλό όταν επιλέγουμε -edge_selection 3, δηλαδή δηλαδή επιλογή ακμής για να προστίθεται το μέγιστο εμβαδόν και χαμηλό όταν επιλέγουμε -edge_selection 2, δηλαδή επιλογή ακμής για να προστίθεται το ελάχιστο εμβαδόν, ενώ γύρω στο μισό όταν έχουμε τυχαία επιλογή ακμής, -edge_selection 1. Σχετικά με τον χρόνο κατασκευής, παρατηρούμε ότι είναι χαμηλός όταν έχουμε τυχαία επιλογή ακμής καθώς απλώς εισάγουμε μία τυχαία ακμή, ενώ στις άλλες επιλογές, υπάρχουν περισσότεροι υπολογισμοί όπως περιγράφεται παραπάνω, και ο χρόνος είναι μεγαλύτερος. 

Παραδείγματα με τον αυξητικό αλγόριθμο.

./to_polygon -i ../instances/data/images/euro-night-0000200.instance -o ../programs/blah.txt -algorithm incremental -edge_selection 1 -initialization 2a

Algorithm: incremental_edge_selection1_initialization2a
area: 41036990
ratio: 0.530706
construction time: 0.065

./to_polygon -i ../instances/data/images/euro-night-0000200.instance -o ../programs/blah.txt -algorithm incremental -edge_selection 2 -initialization 2b

Algorithm: incremental_edge_selection2_initialization2b
area: 19258862
ratio: 0.249063
construction time: 0.068

./to_polygon -i ../instances/data/images/us-night-0000500.instance -o ../programs/blah.txt -algorithm incremental -edge_selection 3 -initialization 2b

Algorithm: incremental_edge_selection3_initialization2b
area: 93704260
ratio: 0.752762
construction time: 0.354

./to_polygon -i ../instances/data/images/us-night-0000500.instance -o ../programs/blah.txt -algorithm incremental -edge_selection 3 -initialization 2b

Algorithm: incremental_edge_selection3_initialization2b
area: 93704260
ratio: 0.752762
construction time: 0.355

./to_polygon -i ../instances/data/images/paris-0001000.instance -o ../programs/blah.txt -algorithm incremental -edge_selection 3 -initialization 1b

Algorithm: incremental_edge_selection3_initialization1b
area: 211032546
ratio: 0.703285
construction time: 1.083

./to_polygon -i ../instances/data/images/skylake-0004000.instance -o ../programs/blah.txt -algorithm incremental -edge_selection 3 -initialization 1b

Algorithm: incremental_edge_selection3_initialization1b
area: 193064582
ratio: 0.689354
construction time: 19.398

./to_polygon -i ../instances/data/images/protein-0020000.instance -o ../programs/blah.txt -algorithm incremental -edge_selection 2 -initialization 1b

Algorithm: incremental_edge_selection2_initialization1b
area: 28763919898
ratio: 0.259819
construction time: 357.633

Όπως παρατηρούμε οι χρόνοι του αυξητικού αλγορίθμου είναι σημαντικά καλύτεροι σε σχέση με του αλγόριθμου με βάση το ΚΠ. Είναι κάτι το οποίο περιμέναμε καθώς ο δεύτερος έχει περισσότερους υπολογισμούς για την πολυγωνοποίηση. Οι παρατηρήσεις για το edge_selection ισχύουν και εδώ, ενώ το initialization δεν επηρεάζει τους χρόνους.

Καλή Διόρθωση! :D
