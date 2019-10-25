//
//  main.cpp
//  NeuralNetworks
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>

struct Neuron
{
    std::vector<Neuron*> in, out;
    int id;
    
    Neuron()
    {
        static int id = 1;
        this->id = id++;
    }
    
    Neuron* begin(){return this;}
    Neuron* end() {return this+1;}
    
    void connect_to(Neuron& other)
    {
        out.push_back(&other);
        other.in.push_back(this);
    }
    
    template<typename T> void connect_to(T& other)
    {
        for (Neuron& target : other)
            connect_to(target);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Neuron& obj)
    {
        for (Neuron* n : obj.in)
        {
            os << n->id << "\t-->\t[" << obj.id << "]" << std::endl;
        }
        
        for (auto n : obj.out)
        {
            os << "[" << obj.id << "]\t-->\t" << n->id << std::endl;
        }
        return os;
    }
};

struct NeuronLayer : std::vector<Neuron>
{
    NeuronLayer(int count)
    {
        while (count-- > 0)
        {
            emplace_back(Neuron{});
        }
    }
    
    template <typename T> void connect_to(T& other)
    {
        for (auto& from : *this)
            for (auto& to : other)
                from.connect_to(to);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const NeuronLayer& obj)
    {
        for (auto& n : obj)
            os << n;
        return os;
    }
};

int main(int argc, const char * argv[]) {
    Neuron n1, n2;
    n1.connect_to(n2);
    
    std::cout << n1 << n2 << std::endl;
    
    NeuronLayer l1{5};
    Neuron n3;
    l1.connect_to(n3);
    
    std::cout << "Neuron : " << n3.id << std::endl << n3 << std::endl;
    std::cout << "Layer : " << std::endl << l1 << std::endl;
    
    
    NeuronLayer l2{2}, l3{3};
    l2.connect_to(l3);
    std::cout << "Layer l2 : " << std::endl << l2;
    std::cout << "Layer l3 : " << std::endl << l3;
    return 0;
}
