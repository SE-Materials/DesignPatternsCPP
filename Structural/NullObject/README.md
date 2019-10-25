#  NullObject

**A no-op object that saisfies the dependency requirement of some other object.**

When component A uses component B, if typically assumes that B is actually present.
- You inject B, not e.g,. optional<B>
- You do not inject a pointer and then check `nullptr` everywhere

There is no option for telling A not to use an instance of B
- Its use is hard coded.

Thus, we build a no-op, non-functioning inheritor of B and pass that in to A.

Structural or Behavioral ??
- This doesn't has any behavior.

## Notes

* Inherit from the required object.
* Implement the functions with empty body
** Return default values.
** If those values are used, you are in trouble because no way to provide satisfactory null object.
* Supply an instance of the null object in lieu of an actual object.




