#include <iostream>
#include <string>
class MilkCollection {
private:
    int batchId;
    std::string farmerName;
    std::string milkType;
    double quantityLiters;
    double fatPercentage;
    double snf;
    double ratePerLiter;
    double totalAmount;
    static int totalBatches;
    static double totalMilkProcured;
public:
    MilkCollection() {
        this->batchId = 0;
        this->farmerName = "";
        this->milkType = "";
        this->quantityLiters = 0.0;
        this->fatPercentage = 0.0;
        this->snf = 0.0;
        this->ratePerLiter = 0.0;
        this->totalAmount = 0.0;
    }
    inline void computePayment() {
        this->ratePerLiter = this->fatPercentage * 8.5;
        this->totalAmount = this->quantityLiters * this->ratePerLiter;
    }
    void setData(int batchId, std::string farmerName, std::string milkType, 
                 double quantityLiters, double fatPercentage, double snf) {
        this->batchId = batchId;
        this->farmerName = farmerName;
        this->milkType = milkType;
        this->quantityLiters = quantityLiters;
        this->fatPercentage = fatPercentage;
        this->snf = snf;
        this->computePayment();
        totalBatches++;
        totalMilkProcured += this->quantityLiters;
    }
    int getBatchId() const {
        return this->batchId;
    }
    void displayRecord() const {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Batch ID      : " << this->batchId << "\n";
        std::cout << "Farmer Name   : " << this->farmerName << "\n";
        std::cout << "Milk Category : " << this->milkType << "\n";
        std::cout << "Quantity (L)  : " << this->quantityLiters << "\n";
        std::cout << "Fat %         : " << this->fatPercentage << "%\n";
        std::cout << "SNF %         : " << this->snf << "%\n";
        std::cout << "Rate / Liter  : INR " << this->ratePerLiter << "\n";
        std::cout << "Total Payout  : INR " << this->totalAmount << "\n";
        std::cout << "----------------------------------------\n";
    }
    static void displaySummary() {
        std::cout << "\n========================================\n";
        std::cout << "     DAIRY COLLECTION TANKER SUMMARY    \n";
        std::cout << "========================================\n";
        std::cout << "Total Batches Logged : " << totalBatches << "\n";
        std::cout << "Total Milk in Vat    : " << totalMilkProcured << " Liters\n";
        std::cout << "========================================\n";
    }
    friend void printReceipt(const MilkCollection &mc);
};
int MilkCollection::totalBatches = 0;
double MilkCollection::totalMilkProcured = 0.0;
void printReceipt(const MilkCollection &mc) {
    std::cout << "\n========================================\n";
    std::cout << "        DAIRY AUDITOR OFFICIAL SLIP     \n";
    std::cout << "========================================\n";
    std::cout << "Verified Batch: #" << mc.batchId << "\n";
    std::cout << "Producer      : " << mc.farmerName << " (" << mc.milkType << ")\n";
    std::cout << "Volume Intake : " << mc.quantityLiters << " L\n";
    std::cout << "Fat / SNF     : " << mc.fatPercentage << "% / " << mc.snf << "%\n";
    std::cout << "Net Credited  : INR " << mc.totalAmount << "\n";
    std::cout << "Quality Status: APPROVED FOR VAT STORAGE\n";
    std::cout << "========================================\n";
}
bool isDuplicateKey(MilkCollection records[], int count, int newId) {
    for (int i = 0; i < count; i++) {
        if (records[i].getBatchId() == newId) {
            return true;
        }
    }
    return false;
}
int main() {
    const int MAX_RECORDS = 50;
    MilkCollection records[MAX_RECORDS];
    MilkCollection* ptrRecords = records; 
    int recordCount = 0;
    int choice = 0;
    while (choice != 5) {
        std::cout << "\n==== DAIRY MILK COLLECTION & QUALITY SYSTEM ====\n";
        std::cout << "1. Add Milk Intake Entry (Create)\n";
        std::cout << "2. View All Intake Entries (Read)\n";
        std::cout << "3. View Vat Aggregation Summary (Static Metric)\n";
        std::cout << "4. Generate Auditor Slip (Friend Function)\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your selection (1-5): ";
        std::cin >> choice;
        if (choice == 1) {
            if (recordCount >= MAX_RECORDS) {
                std::cout << "Collection batch storage limit reached.\n";
                continue;
            }
            int id;
            std::cout << "Enter Unique Batch ID: ";
            std::cin >> id;
            if (isDuplicateKey(records, recordCount, id)) {
                std::cout << "Error: Batch ID " << id << " already exists in system. Duplicate rejected.\n";
                continue;
            }
            std::string name;
            std::cout << "Enter Farmer Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            int typeChoice;
            std::string type = "Cow";
            std::cout << "Select Milk Type (1. Cow, 2. Buffalo): ";
            std::cin >> typeChoice;
            if (typeChoice == 2) {
                type = "Buffalo";
            }
            double qty;
            std::cout << "Enter Quantity in Liters (> 0): ";
            std::cin >> qty;
            if (qty <= 0.0 || qty > 1000.0) {
                std::cout << "Invalid volume entered. Batch rejected.\n";
                continue;
            }
            double fat;
            std::cout << "Enter Measured Fat % (3.0 - 12.0): ";
            std::cin >> fat;
            if (fat < 3.0 || fat > 12.0) {
                std::cout << "Fat percentage outside acceptable milk standard limits (3.0 - 12.0).\n";
                continue;
            }
            double snf;
            std::cout << "Enter Measured SNF % (7.0 - 10.5): ";
            std::cin >> snf;
            if (snf < 7.0 || snf > 10.5) {
                std::cout << "SNF percentage outside acceptable purity limits (7.0 - 10.5).\n";
                continue;
            }
            (ptrRecords + recordCount)->setData(id, name, type, qty, fat, snf);
            recordCount++;
            std::cout << "Batch successfully logged and accepted into cold storage vat.\n";
        } else if (choice == 2) {
            if (recordCount == 0) {
                std::cout << "No milk intake records recorded yet.\n";
            } else {
                for (int i = 0; i < recordCount; i++) {
                    (ptrRecords + i)->displayRecord();
                }
            }
        } else if (choice == 3) {
            MilkCollection::displaySummary();
        } else if (choice == 4) {
            if (recordCount == 0) {
                std::cout << "No collection records available for audit.\n";
                continue;
            }
            int searchId;
            std::cout << "Enter Batch ID for Auditor Verification: ";
            std::cin >> searchId;
            bool found = false;
            for (int i = 0; i < recordCount; i++) {
                if ((ptrRecords + i)->getBatchId() == searchId) {
                    printReceipt(*(ptrRecords + i));
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << "Batch ID not found in intake log.\n";
            }
        } else if (choice == 5) {
            std::cout << "Shutting down collection portal.\n";
        } else {
            std::cout << "Invalid choice. Please select from 1 to 5.\n";
        }
    }
    return 0;
}