```
find . -type f -name "*.hpp" -print0 | xargs -0 sed -i '' -e 's/ClassAttributeProperties/ClassAttributes/g'

find . -type f -name "*.cpp" -print0 | xargs -0 sed -i '' -e 's/ClassAttributeProperties/ClassAttributes/g'

find . -type f -name "*.q.yml" -print0 | xargs -0 sed -i '' -e 's/ClassAttributeProperties/ClassAttributes/g'
```
