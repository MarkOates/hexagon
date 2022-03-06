# Proceedure for Renaming a Component


## Move the Files

```
- If there is a quintessence file:
  - Rename/Move the quintessence and test files to the new locations/filenames
  - if there is a documentation file, move it to the new location/filename
  - remove the generated hpp and cpp files
  - generate the consequntial files (cpp/hpp) from the new quintessence location with `$ make quintessence`
- If there is not a quintessence file:
  - move the header, source, and test files to the new locations/filenames
  - if there is a documentation file, move it to the new location/filename
```

## Rename All Symbols and Include Files In the Project's Codebase 

```
- find-replace the symbol in all files (except git directory, see below for options)
- find-replace the header filenames. These will appear in hpp/cpp #include directives, and under items in the "dependencies:" section of quintessence files.
- find-replace test names, and test fixture names (Wicked_Entities_Zones_BaseTest)
```

## Warnings and Concerns to Look out for

```
! there will be instance variable names that may need to be changed.
! there may be "type" names in enums that need to be changed, either as constants `TYPE_NAME` or as type strings `"Type::Name"`.
! there may be other function names (members of other classes) that use a snake_case variant of the name.
! there may be exception error messages that have changed.
! if the component has been symlinked by other projects, the symlinks will be broken and those projects will not build until they are updated as well.

```

## Example
```
std::string component_name = "Wicked/Zones/Rectangle3D";
std::string new_component_name = "Wicked/Entities/Zones/Rectangle3D";
```

Of those two, the following symbols are likely present in the codebase:

```
Wicked::Zones::Rectangle3D -> Wicked::Entities::Zones::Rectangle3D
Wicked/Zones/Rectangle3D -> Wicked/Entities/Zones/Rectangle3D
Wicked_Zones_Rectangle3D -> Wicked_Entities_Zones_Rectangle3D
```

You can rename the instances recursively using a shell command. Here are two
examples (using the example component names from above).

### Option 1 (preferred)

```
git grep -lz 'Wicked::Zones::Rectangle3D' | xargs -0 perl -i'' -pE "s/Wicked::Zones::Rectangle3D/Wicked::Entities::Zones::Rectangle3D/g"
git grep -lz 'Wicked\/Zones\/Rectangle3D' | xargs -0 perl -i'' -pE "s/Wicked\/Zones\/Rectangle3D/Wicked\/Entities\/Zones\/Rectangle3D/g"
git grep -lz 'Wicked_Zones_Rectangle3D' | xargs -0 perl -i'' -pE "s/Wicked_Zones_Rectangle3D/Wicked_Entities_Zones_Rectangle3D/g"
```

### Option 2 (however, will also bork with .git/ folder)
```
find ./ -type f -exec sed -i -e 's/apple/orange/g' {} \;
```

### If Something Goes Wrong

You can reset your code with `git` command.

Look into either: `git clean -n`, `git clean -f`, or `git reset` and `git checkout` with `-hard` flag.

