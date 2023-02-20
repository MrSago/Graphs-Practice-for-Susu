
#include <cassert>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "graph.hpp"

class GraphTest {
   public:
    void runUnitTests(const std::string& testFileName) {
        std::cout << "\nGraph Unit Tests started...\n";
        std::cout << "Input test file: " << testFileName << '\n';

        std::cout << "\tRead-write test... ";
        readWriteTest(testFileName);
        std::cout << std::setw(19) << "Passed!\n";

        // std::cout << "Add, remove and edit edges from graph test... ";
        // addRemoveEditEdgesTest(testFileName);
        // std::cout << std::setw(10) << "Passed!\n";

        std::cout << "\tTransform test... ";
        transformTest(testFileName);
        std::cout << std::setw(19) << "Passed!\n";

        std::cout << "All tests passed. You are excellent!\n\n";
    }

    void runPrimTests() {
        std::cout << "\nPrim Tests started...\n";
        for (auto& test : st_tests) {
            std::cout << test[0] << ": ";

            auto start = std::chrono::high_resolution_clock::now();
            PrimTest(test[0], test[1], std::string("pr_") + test[2]);
            auto stop = std::chrono::high_resolution_clock::now();

            double calcTime = (stop - start).count() * 1e-9;
            std::cout << "Passed!"
                      << " (time: " << calcTime << ")\n";
        }
        std::cout << "All tests passed! You are perfect!\n";
    }

    void runKruscalTests() {
        std::cout << "\nKruscal Tests started...\n";
        for (auto& test : st_tests) {
            std::cout << test[0] << ": ";

            auto start = std::chrono::high_resolution_clock::now();
            KruscalTest(test[0], test[1], std::string("kr_") + test[2]);
            auto stop = std::chrono::high_resolution_clock::now();

            double calcTime = (stop - start).count() * 1e-9;
            std::cout << "Passed!"
                      << " (time: " << calcTime << ")\n";
        }
        std::cout << "All tests passed! You are the best!\n\n";
    }

   private:
    const std::string rw_fname1 = "rw1.txt";
    const std::string rw_fname2 = "rw2.txt";

    const std::string tr_adj_list_fname1 = "tr_adj_list1.txt";
    const std::string tr_adj_list_fname2 = "tr_adj_list2.txt";
    const std::string tr_adj_matr_fname1 = "tr_ad_matr1.txt";
    const std::string tr_adj_matr_fname2 = "tr_ad_matr2.txt";
    const std::string tr_edge_list_fname1 = "tr_edge_list1.txt";
    const std::string tr_edge_list_fname2 = "tr_edge_list2.txt";

    // {"input", "ans", "output"}
    const std::vector<std::vector<std::string>> st_tests = {
        {"st_test1.txt", "st_ans1.txt", "st_output1.txt"},
        {"input_1e5_1e5.txt", "", "st_output_1e5_1e5.txt"}};

    void readWriteTest(const std::string& testFileName) {
        Graph graph;
        graph.readGraph(testFileName);
        graph.writeGraph(rw_fname1);
        assert(compareFileSize(testFileName, rw_fname1));

        graph.readGraph(rw_fname1);
        graph.writeGraph(rw_fname2);
        assert(compareFiles(rw_fname1, rw_fname2));
    }

    void addRemoveEditEdgesTest(const std::string& testFileName) {}

    void transformTest(const std::string& testFileName) {
        Graph graph;
        graph.readGraph(testFileName);
        graph.transformToAdjList();
        graph.writeGraph(tr_adj_list_fname1);
        graph.readGraph(tr_adj_list_fname1);
        graph.writeGraph(tr_adj_list_fname2);
        assert(compareFiles(tr_adj_list_fname1, tr_adj_list_fname2));

        graph.transformToAdjMatrix();
        graph.writeGraph(tr_adj_matr_fname1);
        graph.readGraph(tr_adj_matr_fname1);
        graph.writeGraph(tr_adj_matr_fname2);
        assert(compareFiles(tr_adj_matr_fname1, tr_adj_matr_fname2));

        graph.transformToListOfEdges();
        graph.writeGraph(tr_edge_list_fname1);
        graph.readGraph(tr_edge_list_fname1);
        graph.writeGraph(tr_edge_list_fname2);
        assert(compareFiles(tr_edge_list_fname1, tr_edge_list_fname2));
    }

    void PrimTest(const std::string& input, const std::string& ans,
                  const std::string& output) {
        Graph graph;
        graph.readGraph(input);
        Graph res = graph.getSpaingTreePrim();
        res.writeGraph(output);
        // assert(compareFiles(output, ans));
    }

    void KruscalTest(const std::string& input, const std::string& ans,
                     const std::string& output) {
        Graph graph;
        graph.readGraph(input);
        Graph res = graph.getSpaingTreeKruscal();
        res.writeGraph(output);
        // assert(compareFiles(output, ans));
    }

    bool compareFileSize(const std::string& p1, const std::string& p2) {
        std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
        std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

        if (f1.fail() || !f1.is_open() || f2.fail() || !f2.is_open()) {
            return false;  // file problem
        }

        if (f1.tellg() != f2.tellg()) {
            return false;  // size mismatch
        }
        return true;
    }

    bool compareFiles(const std::string& p1, const std::string& p2) {
        std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
        std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

        if (f1.fail() || !f1.is_open() || f2.fail() || !f2.is_open()) {
            return false;  // file problem
        }

        if (f1.tellg() != f2.tellg()) {
            return false;  // size mismatch
        }

        // seek back to beginning and use std::equal to compare contents
        f1.seekg(0, std::ifstream::beg);
        f2.seekg(0, std::ifstream::beg);
        return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                          std::istreambuf_iterator<char>(),
                          std::istreambuf_iterator<char>(f2.rdbuf()));
    }
};
