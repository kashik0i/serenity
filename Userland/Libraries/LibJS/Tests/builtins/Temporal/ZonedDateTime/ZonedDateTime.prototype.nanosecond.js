describe("correct behavior", () => {
    test("basic functionality", () => {
        const timeZone = new Temporal.TimeZone("UTC");
        const zonedDateTime = new Temporal.ZonedDateTime(123n, timeZone);
        expect(zonedDateTime.nanosecond).toBe(123);
    });
});

test("errors", () => {
    test("this value must be a Temporal.ZonedDateTime object", () => {
        expect(() => {
            Reflect.get(Temporal.ZonedDateTime.prototype, "nanosecond", "foo");
        }).toThrowWithMessage(TypeError, "Not a Temporal.ZonedDateTime");
    });
});
