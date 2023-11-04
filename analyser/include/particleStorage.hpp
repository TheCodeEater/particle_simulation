//
// Created by Giacomo Errani on 04/11/23.
//

#ifndef ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
#define ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP

#include "Definitions.hpp"
#include "TH1.h"
#include <unordered_map>

namespace BASE_NS{
    /**
     * This class is used to store particle data
     */
    class particleStorage: public TObject{
        using key=std::string;
        public:
            //store in unordered map th1 float histograms
            using HistContainer=std::unordered_map<key,TH1F>;
            /**
             * Construct empty object
             */
            particleStorage()=default;
            /**
             * Construct the storage object from an already existing container
             * Note: the container is internally moved
             * @param cont The container holding the histogram requested
             */
            explicit particleStorage(HistContainer const& cont): fHistContainer{std::move(cont)}{}
            /**
             * Register a new histogram into the container
             * @tparam histArgs Arguments to be forwarded to the TH1F constructor
             * @param k Key used to identify the histogram
             * @param args Arguments used to construct the histogram
             */
            template<typename ...histArgs>
            void addHistogram(key const& k,histArgs&& ...args){
                //check that if does exist
                if(fHistContainer.find(k)!=fHistContainer.end()){
                    throw std::runtime_error{"Key already exists! Key: "+k};
                }
                //forward hist construction arguments to hist ctor
                //pass key first to be the 1st member of pair (underlying node)
                fHistContainer.emplace(k,std::forward<histArgs>(args)...);
            }
            /**
             * Get the underlying container - const version
             * @return Const reference to the underlying container
             */
            [[nodiscard]] HistContainer const& GetContainer() const{
                return fHistContainer;
            }
        /**
         * Get the underlying container - non const version
         * @return Reference to the underlying container
         */
            HistContainer& GetContainer(){
                return fHistContainer;
            }

        ClassDefOverride(particleStorage,1);
    private:
        HistContainer fHistContainer; ///Container holding histograms
    };
}

#endif //ROOT_TEMPLATE_PROJECT_PARTICLESTORAGE_HPP
