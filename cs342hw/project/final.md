Group Members
---
* Gregory N. Schmit

Issue
---
I am implementing a feature for issue #260
(https://github.com/decebals/pippo/issues/260). I have successfully implemented
the feature, however they actually want me to use a built-in method
`Router.uriFor()` to implement it. I am going to do this, but my current code
does achieve the originally stated goals of the feature.

How to Test
---
You should use Maven to install the original version of Pippo. Then, build a
project by going to a directory of your choosing and running the following
command:

    $ mvn archetype:generate \
      -DarchetypeGroupId=ro.pippo \
      -DarchetypeArtifactId=pippo-quickstart \
      -DarchetypeVersion=0.9.0 \
      -DgroupId=com.mycompany \
      -DartifactId=mytestproject

You can run your web app using the command `mvn compile exec:java`.

We need to do a couple things:
1. Switch from Freemarker to Pebble as our template engine.
2. Create a template to test stuff.
3. Setup your Pippo Application.
4. Switch from official Pebble to my Pebble.

So, edit `pom.xml` and change the Freemarker dependency to this (you only have
to change the `artifactId`):

    <dependency>
        <groupId>ro.pippo</groupId>
        <artifactId>pippo-pebble</artifactId>
        <version>${pippo.version}</version>
    </dependency>

Now, create the file `src/main/resources/templates/hi.peb` and edit it thusly:

    <!DOCTYPE html>
    <html>
      <head>
        <title>Test Greg's Pebble Feature</title>
        <style>
          html { font-family: Arial, Helvetica, sans-serif; }
          .main-hr { border-color: #333333; }
        </style>
      </head>
      <body style="font-family: Arial, Helvetica, sans-serif;">
        <h1>Pebble <code>route</code> Template Function Tests</h1>
        <hr class="main-hr">
        <h2>Test simple variable insertion:</h2>
        <p><code>3 days ago it was: {{ myDate }}</code></p>
        <hr>
        <h2>Test template filter prettyTime:</h2>
        <p><code>This was: {{ myDate | prettyTime }}</code></p>
        <hr>
        <h2>3 uses of the <code>route</code> template function:</h2>
        <br>
        <p>Should see: <code>/main/app/dir</code></p>
        <p>Output: <code>{{ route("/main/", "/app/", "/dir/") }}</code></p>
        <br>
        <p>Should see: <code>/main/app/dir</code></p>
        <p>Output: <code>{{ route("/main/", app_dir) }}</code></p>
        <br>
        <p>Should see: <code>/app/post/8</code></p>
        <p>Output: <code>{{ route("/app/post", post_id) }}</code></p>
      </body>
    </html>

This is two random tests just to make sure Pebble is working, and then three
tests of my `route` template function.

Now, edit `src/main/java/com/mycompany/PippoApplication.java` and set your
onInit method to this:

    @Override
    protected void onInit() {
        GET("/", routeContext -> {
            routeContext.setLocal("myDate", Date.from(LocalDateTime.now()
              .minusDays(3)
              .atZone(ZoneId.systemDefault()).toInstant()
            ));
            routeContext.setLocal("app_dir", "/app/dir");
            routeContext.setLocal("post_id", 8);
            routeContext.render("hi");
        });
    }

Also, add the following to your `import` list in the same file:

    import java.time.LocalDateTime;
    import java.time.ZoneId;
    import java.util.Date;

Run `mvn compile exec:java` and connect to http://localhost:8338 with a
browser. You should get a big fat error, since `route` isn't a thing.

Now, `cd` to wherever you have downloaded my version of Pippo, and then do
`cd pippo-template-parent/pippo-pebble` and then run:

    $ mvn compile
    $ mvn install

Now you have my version of Pebble. `cd` back to your test project directory.
Edit `pom/xml` and change the version of your dependancy Pippo-Pebble to
`1.5.0-SNAPSHOT-gnsdev`, like so:

    <dependency>
        <groupId>ro.pippo</groupId>
        <artifactId>pippo-pebble</artifactId>
        <version>1.5.0-SNAPSHOT-gnsdev</version>
    </dependency>

Now you should be able to run `mvn compile exec:java` to run your web
application.

Connecting to http://localhost:8338 should now yield expected results,
showing that I implemented the `route` template function.

Where is this code?
---
My version of Pippo is located at https://github.com/schmitgreg/pippo.

Specifically, I created the Java file located at `pippo/pippo-template-parent/pippo-pebble/src/main/java/ro/pippo/pebble/RouteExtension.java`
