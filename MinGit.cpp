#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


struct Commit {
    string hash;       
    string message;     
    Commit* parent;     

    Commit(string h, string msg, Commit* p = nullptr) : hash(h), message(msg), parent(p) {}
};
class VersionControl {
private:
    unordered_map<string, Commit*> branches;  
    Commit* HEAD;                             
public:
    VersionControl() : HEAD(nullptr) {}
    void commit(const string& hash, const string& message) {
        HEAD = new Commit(hash, message, HEAD);
        cout << "Commit created: " << hash << " - " << message << endl;
    }
    void branch(const string& branchName) {
        if (HEAD) {
            branches[branchName] = HEAD;
            cout << "Branch '" << branchName << "' created at commit " << HEAD->hash << endl;
        } else {
            cout << "No commits exist to branch from." << endl;
        }
    }
    void checkout(const string& target) {
        if (branches.find(target) != branches.end()) {
            HEAD = branches[target];
            cout << "Checked out branch '" << target << "' at commit " << HEAD->hash << endl;
        } else {
            cout << "Invalid branch or commit hash!" << endl;
        }
    }
    void showHistory() {
        if (!HEAD) {
            cout << "No commits in history." << endl;
            return;
        }
        Commit* temp = HEAD;
        cout << "\n--- Commit History ---\n";
        while (temp) {
            cout << temp->hash << " - " << temp->message << endl;
            temp = temp->parent;
        }
        cout << "----------------------\n";
    }
};
void showMenu() {
    cout << "\nMiniGit CLI\n";
    cout << "1. Commit\n";
    cout << "2. Create Branch\n";
    cout << "3. Checkout Branch\n";
    cout << "4. Show History\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    VersionControl vcs;
    int choice;
    string inputHash, inputMessage, inputBranch;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();  

        switch (choice) {
            case 1:
                cout << "Enter commit hash: ";
                getline(cin, inputHash);
                cout << "Enter commit message: ";
                getline(cin, inputMessage);
                vcs.commit(inputHash, inputMessage);
                break;

            case 2:
                cout << "Enter new branch name: ";
                getline(cin, inputBranch);
                vcs.branch(inputBranch);
                break;

            case 3:
                cout << "Enter branch name to checkout: ";
                getline(cin, inputBranch);
                vcs.checkout(inputBranch);
                break;

            case 4:
                vcs.showHistory();
                break;

            case 5:
                cout << "Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
