/*=============================================================================

  Library: CppMicroServices

  Copyright (c) The CppMicroServices developers. See the COPYRIGHT
  file at the top-level directory of this distribution and at
  https://github.com/CppMicroServices/CppMicroServices/COPYRIGHT .

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  =============================================================================*/
#include "../src/metadata/MetadataParser.hpp"
#include "../src/metadata/MetadataParserFactory.hpp"
#include "Mocks.hpp"
#include "gtest/gtest.h"

using namespace cppmicroservices;

namespace cppmicroservices
{
    namespace scrimpl
    {
        namespace metadata
        {

            TEST(MetadataParserTest, ManifestVersionInvalid)
            {
                auto logger = std::make_shared<FakeLogger>();
                EXPECT_THROW(MetadataParserFactory::Create(0, logger);, std::runtime_error);
                EXPECT_THROW(MetadataParserFactory::Create(2, logger);, std::runtime_error);
            }

        } // namespace metadata
    }     // namespace scrimpl
} // namespace cppmicroservices
