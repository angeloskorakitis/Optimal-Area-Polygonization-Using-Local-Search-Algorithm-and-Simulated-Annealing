2023-emiris-k23-assignment-2

Project Παραδοτέο 2

Ομάδα:

Άγγελος Κορακίτης ΑΜ 1115201900087 (sdi1900087) Σταύρος Τρουπής ΑΜ 1115201900191 (sdi1900191)

Έχουν υλοποιηθεί οι αλγόριθμοι 1 και 2 της εκφώνησης, ο local search και ο simulated annealing.

Ο Άγγελος (sdi1900087) ασχολήθηκε με την υλοποίηση του local search αλγορίθμου. Ο Σταύρος (sdi1900191) ασχολήθηκε με την υλοποίηση του simulated annealing αλγορίθμου.

Περιεχόμενα README:

    Kατάλογος αρχείων.

    Περιγραφή αρχείων.

    Οδηγίες μεταγλώττισης και χρήσης του προγράμματος.

    Περιγραφή κώδικα.

    Παραδείγματα εκτέλεσης και σχολιασμός τους.

    Κατάλογος αρχείων: . ├── build │ └── CMakeFiles │
    ├── include │ ├── Local_Search_Area-Optimal_Polygonization.hpp │ ├── Polygonization_Using_Convex_Hull_Algorithm.hpp │ ├── Polygonization_Using_Incremental_Algorithm.hpp │ └── Utilities.hpp │
    ├── modules │ ├── Local_Search_Area-Optimal_Polygonization.cpp │ ├── Polygonization_Using_Convex_Hull_Algorithm.cpp │ ├── Polygonization_Using_Incremental_Algorithm.cpp │ └── Utilities.cpp └── programs ├── CMakeLists.txt └── main.cpp

    Περιγραφή αρχείων:

    Η δομή των αρχείων είναι αυτή που φαίνεται στο παραπάνω δέντρο. Στο αρχείο build περιέχονται τα CMakeFiles, εκεί γίνεται και η μεταγλώττιση του προγράμματος με τη χρήση της εντολής make. Στην συνέχεια περιέχονται τα include και modules τα οποία περιέχουν τον κώδικα που γράψαμε για την υλοποίηση των αλγορίθμων. Στο αρχείο include, όπως φανερώνει και το όνομα του, περιέχονται τα .hpp αρχεία, τα οποία με την σειρά τους περιέχουν τις δηλώσεις των συναρτήσεων και μια περιγραφή για το τι κάνει η κάθεμια. Πιο συγκεκριμένα στο include: - Polygonization_Using_Convex_Hull_Algorithm.hpp : Περιέχει τις δηλώσεις των συναρτήσεων που χρειάστηκαν για την υλοποίηση του αλγορίθμου με βάση το κυρτό περίβλημα. - Polygonization_Using_Incremental_Algorithm.hpp : Περιέχει τις δηλώσεις των συναρτήσεων που χρειάστηκαν για την υλοποίηση του αυξητικού αλγορίθμου. - Local_Search_Area-Optimal_Polygonization.hpp : Περιέχει τις δηλώσεις των συναρτήσεων που χρειάστηκαν για την υλοποίηση του αλγορίθμου τοπικής αναζήτησης - Utilities.hpp : Περιέχει τις δηλώσεις βοηθητικών συναρτήσεων που που δεν σχετίζονται άμεσα με τους αλγόριθμους που υλοποιήθηκαν. Αυτές είναι printing functions που χρησιμοποιήσαμε κατα την υλοποίηση των αλγορίθμων για έλεγχο των πολυγώνων, καθώς και των συναρτήσεων για την ανάγνωση από το αρχείο εισόδου, των σημείων, αλλα και το γράψιμο των αποτελεσμάτων σε αρχείο εξόδου, σύμφωνα με την εκφώνηση. Επίσης, στο συγκεκριμένο αρχείο υπάρχουν οι δηλώσεις των βιβλιοθηκών που χρειαστήκαμε, όπως επίσης και μερικά typedefs για την αναγνωσιμότητα του κώδικα. 
    Στο αρχείο modules περιέχονται τα αντίστοιχα των παραπάνω αρχείων επικεφαλίδας, .cpp αρχεία, με σχολιασμό για την λειτουργία της κάθε συνάρτησης που περιέχεται. Πιο συγκεκριμένα στο modules: - Polygonization_Using_Convex_Hull_Algorithm.cpp - Polygonization_Using_Incremental_Algorithm.cpp - Local_Search_Area-Optimal_Polygonization.cpp - Utilities.cpp Τέλος, υπάρχει ο κατάλογος programs που περιέχει το main.cpp, όπου γίνεται μια επεξεργασία των παραμέτρων εισόδου και καλούνται οι απαραίτητες συναρτήσεις από τα αρχεία που περιγράφηκαν παραπάνω για την εκτέλεση των αλγορίθμων σύμφωνα με τις οδηγίες της εκφώνησης, όπως επίσης και το αρχείο CMakeLists.txt το οποίο έχει τις απαραίτητες πληροφορίες για το πρόγραμμα μας, προκειμένου να μπορεί να τρέχει το cmake και να δημιουργεί το απαραίτητο MakeFile για την μεταγλώττιση του προγράμματος.

    Οδηγίες μεταγλώττισης και χρήσης του προγράμματος:

    Στον κατάλογο /programs εκτελούμε: cmake -DCMAKE_BUILD_TYPE=Release -S . -B ../build

    Για να κάνω compile και run εκτελούμε στον κατάλογο /build: 
    
    Compile:
    make 
    
    Run:
    ./optimal_polygon –i –o -algorithm_initial –algorithm <local_search or simulated_annealing> -L [L parameter according to algorithm] –max [maximal area polygonization] –min [minimal area polygonization] –threshold [in local search] –annealing <"local" or "global" or "subdivision" in simulated annealing>

    (ΠΡΟΣΟΧΗ! Αν ακολουθηθούν τις παραπάνω οδηγίες, για να γίνει η μεταγλώττιση πρέπει να βρίσκεστε στον κατάλογο /build καθώς εκεί περιέχεται το MakeFile και δημιουργείται το εκτελέσιμο optimal_polygon. Χρειάζεται να λαμβάνετε υποψιν σας και στον προσδιορισμό του input και output file.)

    Περιγραφή κώδικα:

Όσον αφορά την επιλογή αλγορίθμου με βάση το πρώτο παραδοτέο, στον αυξητικό αλγόριθμο το initialization είναι πάντα 1a ενώ το edge_selection ειναι min, max ανάλογα με το αντίστοιχο όρισμα που δίνεται από την γραμμή εντολών. Στον αλγόριθμο με βάση το κυρτό περίβλημα...()





Όσον αφορά τον Local Search αλγόριθμο:

Περιγραφή: (a) Επιλογή αλγορίθμου για την αρχική πολυγωνοποίηση σημειοσυνόλου από την 1η εργασία, όπως αναφέρεται παραπάνω. (b) Για κάθε ακμή του πολυγώνου βρίσκουμε ένα path από 1 εως L σημεία. Εφαρμόζουμε τις αλλαγές στο πολύγωνο όπως ακριβώς περιγράφεται στον αλγόριθμο των διαφανειών, διαγραφουμε το κάθε σημείο του path της πολυγωνικής γραμμής απο την θέση που βρίσκεται και τα προσθέτω το σημείο αυτο πίσω απο το target σημείο της ακμής που είχαμε επιλέξη αρχικά. Το επόμενο σημείο του path το διαγράφουμε και αυτη τη φορα το προσθέτουμε πίσω απο το προηγούμενο σημείο. Αυτή η διαδικασία συνεχίζεται για όλο το path και στον κώδικα υλοποιείται από την local_search_step συνάρτηση. Συνεχίζουμε αυτές τις αλλαγές μέχρι η βελτίωση να είναι το πολύ όσο το threshold.

Η παραπάνω περιγραφή αφορά σύνολα σημείων μεχρι 500 σημεία. Για σύνολα μεγαλύτερα απλώς επιλέγουμε 20 τυχαίες ακμές για να κανουμε την παραπάνω διαδικασία και όχι όλη την πολυγωνική γραμμή. Αυτό γίνεται για λόγους κόστους καθώς πειραματικά παρατηρούμε ότι αυξάνονται πολύ οι χρόνοι τους οποίους χρειάζεται ο αλγόριθμος. Το παραπάνω το είχαμε συζητήσει στην παράδοση του μαθήματος.

H συνάρτηση με την οποία υπολογίζουμε το delta είναι η (temp_area - area)/convex_hull_area, δηλαδή το εμβαδο της νεας πολυγωνικής γραμμής μείον της παλιάς προς το εμβαδόν του κυρτού περιβλήματος






Όσον αφορά το simulated annealing:

Στο αρχείο Simulated_Annealing.cpp περιέχεται ο πηγαίος κώδικας της υλοποίησης του simulated annealing. 
Υλοποιούνται και τα δύο Local και Global step. 

Για το global step. Το Global step υλοποιείται με την διαγραφή ενός τυχαίου σημείου του πολυγώνου και την εισαγωγή του ξανά
στο πολύγωνο σε τυχαίο σημείο, με τέτοιο τρόπο ώστε το πολύγωνο να παραμένει απλό και οι νέες ακμές που δημιουργούνται να μην
τέμνονται με άλλες ακμές του πολυγώνου ή μεταξύ τους. Η συνάρτηση global_step δέχεται ως όρισμα ένα πολύγωνο και επιχειρεί
σε αυτό μία global step αλλαγή, αν η αλλαγή είναι αποδεκτή, επιστρέφει true και το πολύγωνο αλλαγμένο, αν δεν είναι 
αποδεκτή, επιστρέφει false και το πολύγωνο στην αρχική του μορφή. 


Για το loal step. Το Local step υλοποιείται με την διαγραφή ενός τυχαίου σημείου του πολυγώνου και την εισαγωγή του ξανά
στο πολύγωνο μία θέση πιο πίσω από αυτήν που βρισκόταν αρχικά, με τέτοιο τρόπο ώστε το πολύγωνο να παραμένει απλό και οι νέες ακμές που δημιουργούνται να μην
τέμνονται με άλλες ακμές του πολυγώνου ή μεταξύ τους. Ο έλεγχος της τομής των ακμών υλοποιείται μέσω της δομής Kd-tree
της CGAL. Μέσω της δομής εντοπίζουμε τα σημεία του πολυγώνου που βρίσκονται στο νοητό ορθογώνιο που δημιουργούν τα 
σημεία της τοπικής αλλαγής και ελέγχουμε μόνο τις ακμές που ξεκινούν από τα σημεία αυτά. Έτσι δεν χρειάζεται να ελέγξουμε 
όλο το πολύγωνο. Η συνάρτηση local_step δέχεται ως όρισμα το πολύγωνο και το kd-tree με τα σημεία και επιχειρεί στο πολύγωνο
μία local step αλλαγή. Αν η αλλαγή είναι αποδεκτή (ο έλεγχος γίνεται καλώντας κατάλληλες συναρτήσεις step_is_valid και edges_in_box_intersect),
επιστρέφει true και το πολύγωνο αλλαγμένο, αν δεν είναι αποδεκτή, επιστρέφει false και το πολύγωνο στην αρχική του μορφή. 




Όσον αφορά το spatial subdivision:

Στο αρχείο Spatial_Subdivision.cpp περιέχεται ο πηγαίος κώδικας της υλοποίησης του spatial subdivision.

Το spatial subdivision χωρίζει το σημειοσύνολο σε spals (μικρότερα σημειοσύνολα όπως ορίζονται στην εκφώνηση).
Κατά τη διάρκεια του διαχωρισμού, διασφαλίζεται ότι το κάθε spal τηρεί τις προϋποθέσεις που τίθενται, που αφορούν
την μονοτονία των ακριανών ακμών του κάτω μέρους του convex hull του spal.

Για κάθε ένα από αυτά τα spals καλείται μια παραλλαγή του αλγόριθμου convex_hull της πρώτης εργασίας (spatial convex hull), η οποία λειτουργεί
με παρόμοιο τρόπο με τον απλό convex hull, διασφαλίζοντας, όμως, ότι οι "μαρκαρισμένες" ακμές του spal παραμένουν ως έχουν
και δεν αλλάζουν. Έτσι, για κάθε spal έχουμε μια πολυγωνοποίηση που περιέχει τις "μαρκαρισμένες" ακμές. 

Ύστερα, για κάθε τέτοιο πολύγωνο που δημιουργήθηκε από spal καλείται μία παραλλαγή του αλγόριθμου simulated annealing (spatial annealing).
Ο αλγόριθμος αυτός λειτουργεί με παρόμοιο τρόπο με τον απλό simulated annealing, απλώς διασφαλίζει ότι οι "μαρκαρισμένες"
ακμές του πολύγώνου παραμένουν ως έχουν και δεν αλλάζουν. Αυτό επιτυγχάνεται με την κλήση μίας παραλλαγής της συνάρτησης 
global step (spatial global step), η οποία εκτελεί ένα global step στο πολύγωνο, διασφαλίζουντας πάλι ότι οι "μαρκαρισμένες"
ακμές δεν αλλάζουν. 

Έτσι, έχουμε μία σειρά από πολύγωνα, στα οποία έχει εφαρμοστεί το simulated annealing. Τελικά, ενώνουμε τα πολύγωνα
με τον τρόπο που περιγράφεται στην εκφώνηση και καταλήγουμε με ένα μεγάλο τελικό πολύγωνο. 






    Παραδείγματα εκτέλεσης και σχολιασμός τους:

Η μορφή των παραδειγμάτων είναι: <εντολή εκτέλεσης> <αποτέλεσμα εξόδου>

./optimal_polygon -i ../instances/data/images/paris-0000200.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 5 -max -threshold 0.001

Algorithm: incremental_local_search_max area_initial: 197092256 area: 233813130 ratio_initial: 0.724213 ratio: 0.859143 construction time: 117.846

./optimal_polygon -i ../instances/data/images/paris-0000200.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 4 -max -threshold 0.001

Algorithm: incremental_local_search_max area_initial: 207240082 area: 228804018 ratio_initial: 0.744221 ratio: 0.821659 construction time: 332.288

./optimal_polygon -i ../instances/data/images/london-0000015.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 3 -max -threshold 0.001

Algorithm: incremental_local_search_max area_initial: 86055088 area: 121031006 ratio_initial: 0.634368 ratio: 0.892199 construction time: 0.014

./optimal_polygon -i ../instances/data/images/stars-0000010.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 2 -max -threshold 0.001

Algorithm: incremental_local_search_max area_initial: 104930649890 area: 127476507282 ratio_initial: 0.755879 ratio: 0.918291 construction time: 0.001

./optimal_polygon -i ../instances/data/images/paris-0000300.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 5 -min -threshold 0.005

Algorithm: incremental_local_search_min area_initial: 73467662 area: 64573498 ratio_initial: 0.26383 ratio: 0.23189 construction time: 61.687

./optimal_polygon -i ../instances/data/images/us-night-0002000.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 5 -max -threshold 0.001

Algorithm: incremental_local_search_max area_initial: 383442490 area: 383542680 ratio_initial: 0.760347 ratio: 0.760546 construction time: 30.454

./optimal_polygon -i ../instances/data/images/us-night-0000200.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 6 -max -threshold 0.001

Algorithm: incremental_local_search_max area_initial: 83075854 area: 91975332 ratio_initial: 0.78412 ratio: 0.868119 construction time: 139.239

./optimal_polygon -i ../instances/data/images/us-night-0000200.instance -o ../programs/blah.txt -algorithm_initial incremental -algorithm local_search -L 6 -max -threshold 0.01

Algorithm: incremental_local_search_max area_initial: 83075854 area: 86521198 ratio_initial: 0.78412 ratio: 0.816639 construction time: 14.14

Γενικα παρατηρούμε ότι για μεγάλα σύνολα 1000+ σημεία χρειάζονται πολλοί πόροι για να τρέξουμε τον αλγόριθμο με μικρό threshold, μικρότερο από 0.001 και επομένως να έχουμε σημαντικές αλλαγές στην βελτιστοποίηση του εμβαδού.

Εξαρτάται αρκετα και από την γεωμετρία του ίδιου του προβλήματος και το πόσες αλλαγές θα βρει η ευριστική. Για παραδειγμα τρέχοντας δυο διαφορετικά σημειοσύνολα με 200 σημεία και ίδιες παραμέτρους παρατηρούμε μεγάλη διαφορα στα αποτελέσματα...(να πω περισσοτερα)








Καλή Διόρθωση! :D