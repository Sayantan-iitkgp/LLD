#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define st string

// Abstract Template class for Model_Training & Pipeline maintaining the template method
class MLModel
{
public:
    // Template Method defining the steps of the ML Pipeline
    void ML_Pipeline() const
    {
        load_data("data.csv");
        Data_Preprocessing();
        Feature_Engineering();
        Model_Training();
        Model_Evaluation();
        save_model("model.sav");
    }

protected:
    // Concrete Methods
    void load_data(string data_path) const
    {
        cout << "Data Loaded from: " << data_path << endl;
    }

    virtual void Data_Preprocessing() const= 0;

    virtual void Feature_Engineering() const= 0;

    virtual void Model_Evaluation() const= 0;

    // Abstract Method to be implemented by subclasses
    virtual void Model_Training() const= 0;

    void save_model(string model_path) const 
    {
        cout << "Model Saved at: " << model_path << endl;
    }
};

//Derived class implementing the abstract methods for a Decision Tree Model
class DecisionTreeModel : public MLModel
{
protected:
//Any Model can do their own implementation according to their requirement and in any order but the template method ML_Pipeline will ensure the order of execution remains the same.
    void Feature_Engineering() const override
    {
        cout << "Decision Tree: Feature Engineering Completed." << endl;
    }

    void Data_Preprocessing() const override
    {
        cout << "Decision Tree: Data Preprocessing Completed." << endl;
    }

    void Model_Training() const override
    {
        cout << "Decision Tree: Model Training Completed." << endl;
    }

    void Model_Evaluation() const override
    {
        cout << "Decision Tree: Model Evaluation Completed." << endl;
    }
};

//Derived class implementing the abstract methods for a Neural Network Model
class NeuralNetworkModel : public MLModel
{
protected:
    void Data_Preprocessing() const override
    {
        cout << "Neural Network: Data Preprocessing Completed." << endl;
    }

    void Feature_Engineering() const override
    {
        cout << "Neural Network: Feature Engineering Completed." << endl;
    }

    void Model_Training() const override
    {
        cout << "Neural Network: Model Training Completed." << endl;
    }

    void Model_Evaluation() const override
    {
        cout << "Neural Network: Model Evaluation Completed." << endl;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    MLModel* model1 = new DecisionTreeModel();
    model1->ML_Pipeline();

    cout << "-----------------------------" << endl;

    MLModel* model2 = new NeuralNetworkModel();
    model2->ML_Pipeline();

    delete model1;
    delete model2;

    return 0;
}